#include "include/Cenario.h"
#include "include/Raio.h"
#include "include/Camera.h"
#include <limits>
#include <iostream>
#include <fstream>

Cenario::Cenario(Ponto& olho, Janela& janela, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin)
    : olho(olho), janela(janela), camera(nullptr), cor_background(background), n_col(n_col), n_lin(n_lin), canvas(n_col * n_lin * 3) {
    fontes.push_back(&fonte);
}

// construtor para câmera
Cenario::Cenario(Camera* camera, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin)
    : olho(camera->eye), janela(0, 0, camera->d), camera(camera), cor_background(background), n_col(n_col), n_lin(n_lin), canvas(n_col * n_lin * 3), objetoSelecionado(nullptr), pontoSelecionado(0.0f, 0.0f, 0.0f) {
    fontes.push_back(&fonte);
}

void Cenario::adicionarObjeto(ObjetoAbstrato* obj) {
    objetos.push_back(obj);
}

void Cenario::adicionarFonte(FonteIluminacao* fonte) {
    fontes.push_back(fonte);
}

void Cenario::limparFontes() {
    fontes.clear();
}

void Cenario::render() {
    // se tiver câmera, usa o sistema de coordenadas da câmera
    if (camera != nullptr) {
        float delta_x = (camera->xmax - camera->xmin) / n_col;
        float delta_y = (camera->ymax - camera->ymin) / n_lin;

        for (int lin = 0; lin < n_lin; lin++) {
            // calcula y na janela de visualização (de cima para baixo)
            float y = camera->ymax - delta_y/2.0f - lin * delta_y;
            
            for (int col = 0; col < n_col; col++) {
                // calcula x na janela de visualização (da esquerda para direita)
                float x = camera->xmin + delta_x/2.0f + col * delta_x;
                
                unsigned char* pixel = &canvas[(lin * n_col + col) * 3];
                
                // gera direção do raio usando o sistema de coordenadas da câmera
                Vetor d = camera->gerarDirecaoRaio(x, y);
                Raio raio(camera->eye, d);
                
                float t_min = std::numeric_limits<float>::max();
                ObjetoAbstrato* objeto_mais_proximo = nullptr;
                
                for (ObjetoAbstrato* obj : objetos) {
                    float t;
                    if (obj->intersecao(raio, t) && t < t_min) {
                        t_min = t;
                        objeto_mais_proximo = obj;
                    }
                }
                
                if (objeto_mais_proximo != nullptr) {
                    Ponto Pi = raio.equacaoRaio(t_min);
                    Vetor d = raio.direcao;

                    // inicializa cor com componente ambiente (apenas da primeira fonte)
                    Cor cor(0, 0, 0);
                    if (!fontes.empty()) {
                        cor = fontes[0]->I_A.multiComponente(objeto_mais_proximo->Ka);
                    }
                    
                    // quando a intensidade estiver zerada, adiciona um Kdzinho pra iluminar
                    if (fontes[0]->I_F.r == 0 && fontes[0]->I_F.g == 0 && fontes[0]->I_F.b == 0) {
                        Cor corDifusaBase = objeto_mais_proximo->obterCorDifusa(Pi);
                        Cor corDifusaReduzida = corDifusaBase.multiEscalar(0.1f);
                        cor = cor.somarCor(corDifusaReduzida);
                    }

                    // itera sobre todas as fontes de iluminação
                    for (FonteIluminacao* fonte : fontes) {
                        Vetor l = fonte->P_F.subPonto(Pi).normalizado();
                        Raio raio_sombra(Pi, l);
                        bool em_sombra = false;
                        float distancia_luz = fonte->P_F.subPonto(Pi).norma();

                        // verifica se está em sombra em relação a esta fonte
                        for (ObjetoAbstrato* obj : objetos) {
                            if (obj == objeto_mais_proximo) continue;
                            float t_sombra;
                            if (obj->intersecao(raio_sombra, t_sombra) && t_sombra > 0.001f && t_sombra < distancia_luz) {
                                em_sombra = true;
                                break;
                            }
                        }

                        // se não está em sombra, adiciona a contribuição desta fonte
                        if (!em_sombra) {
                            Vetor normal = objeto_mais_proximo->calcularNormal(Pi, d);
                            Vetor observador = d.vetorNegativo();
                            Cor corDifusa = objeto_mais_proximo->obterCorDifusa(Pi);
                            
                            // calcula componentes de iluminação (sem ambiente, já adicionado)
                            Vetor direcaoLuz = fonte->calcularDirecaoLuz(Pi);
                            Vetor reflexao = fonte->calcularVetorReflexao(normal, direcaoLuz);
                            
                            float intensidadeSpot = fonte->calcularIntensidadeSpot(Pi);
                            
                            if (intensidadeSpot > 0.0f) {
                                Cor componenteDifusa = fonte->calcularComponenteDifusa(normal, direcaoLuz, corDifusa);
                                Cor componenteEspecular = fonte->calcularComponenteEspecular(reflexao, observador, objeto_mais_proximo->Ke, objeto_mais_proximo->m);
                                
                                // aplica intensidade de spot light
                                componenteDifusa = componenteDifusa.multiEscalar(intensidadeSpot);
                                componenteEspecular = componenteEspecular.multiEscalar(intensidadeSpot);
                                
                                // soma contribuições desta fonte
                                cor = cor.somarCor(componenteDifusa).somarCor(componenteEspecular);
                            }
                        }
                    }

                    cor.limitar(); // restringe a no max 1
                    cor.escreverNoBuffer(pixel);
                } else {
                    cor_background.escreverNoBuffer(pixel);
                }
            }
        }
    }
}


// importante pra interação no menu
bool Cenario::pick(int mouseX, int mouseY, ObjetoAbstrato*& selecionado, Ponto& pontoImpacto, float& tHit) {
    selecionado = nullptr;
    tHit = std::numeric_limits<float>::max();

    if (camera == nullptr) {
        return false;
    }

    float delta_x = (camera->xmax - camera->xmin) / n_col;
    float delta_y = (camera->ymax - camera->ymin) / n_lin;

    float x = camera->xmin + delta_x / 2.0f + static_cast<float>(mouseX) * delta_x;
    float y = camera->ymax - delta_y / 2.0f - static_cast<float>(mouseY) * delta_y;

    Vetor d = camera->gerarDirecaoRaio(x, y);
    Raio raio(camera->eye, d);

    for (ObjetoAbstrato* obj : objetos) {
        float t;
        if (obj->intersecao(raio, t) && t > 0.0f && t < tHit) {
            tHit = t;
            selecionado = obj;
        }
    }

    if (selecionado != nullptr) {
        pontoImpacto = raio.equacaoRaio(tHit);
        objetoSelecionado = selecionado;
        pontoSelecionado = pontoImpacto;
        return true;
    }
    return false;
}

ObjetoAbstrato* Cenario::getObjetoSelecionado() const {
    return objetoSelecionado;
}

Ponto Cenario::getPontoSelecionado() const {
    return pontoSelecionado;
}

void Cenario::limparSelecao() {
    objetoSelecionado = nullptr;
    pontoSelecionado = Ponto(0.0f, 0.0f, 0.0f);
}