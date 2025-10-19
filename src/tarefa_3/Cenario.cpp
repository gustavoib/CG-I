#include "Cenario.h"
#include "Raio.h"
#include <limits>
#include <iostream>
#include <fstream>

Cenario::Cenario(Ponto& olho, Janela& janela, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin)
    : olho(olho), janela(janela), fonte(fonte), cor_background(background), n_col(n_col), n_lin(n_lin), canvas(n_col * n_lin * 3) {}

void Cenario::adicionarObjeto(ObjetoAbstrato* obj) {
    objetos.push_back(obj);
}

void Cenario::render() {
    float delta_x = janela.w_janela/n_col;
    float delta_y = janela.h_janela/n_lin;
    float z = janela.d_janela;

    for (int lin = 0; lin < n_lin; lin++) {
        float y = janela.h_janela/2.0f - delta_y/2.0f - lin * delta_y;
        
        for (int col = 0; col < n_col; col++) {
            float x = -janela.w_janela/2.0f + delta_x/2.0f + col * delta_x;
            
            unsigned char* pixel = &canvas[(lin * n_col + col) * 3];
            
            Ponto xyz_janela(x, y, z);
            Vetor direcao = xyz_janela.subPonto(olho);
            Vetor d = direcao.normalizado();
            Raio raio(olho, d);
            
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

                Vetor l = fonte.P_F.subPonto(Pi).normalizado();
                Raio raio_sombra(Pi, l);
                bool em_sombra = false;
                float distancia_luz = fonte.P_F.subPonto(Pi).norma();

                for (ObjetoAbstrato* obj : objetos) {
                    if (obj == objeto_mais_proximo) continue;
                    float t_sombra;
                    if (obj->intersecao(raio_sombra, t_sombra) && t_sombra < distancia_luz) {
                        em_sombra = true;
                        break;
                    }
                }

                Cor cor(0,0,0);
                if (em_sombra) {
                    cor = fonte.I_A.multiComponente(objeto_mais_proximo->Ka);
                } else {
                    cor = objeto_mais_proximo->calcularIluminacao(Pi, d, fonte);
                }
                cor.escreverNoBuffer(pixel);
            } else {
                cor_background.escreverNoBuffer(pixel);
            }
        }
    }
}

void Cenario::salvarPPM(const std::string& filename) {
    std::ofstream arquivo(filename, std::ios::binary);
    
    if (!arquivo) {
        std::cerr << "Erro ao criar arquivo: " << filename << std::endl;
        return;
    }
    
    arquivo << "P6\n";
    arquivo << n_col << " " << n_lin << "\n";
    arquivo << "255\n";
    
    arquivo.write(reinterpret_cast<char*>(canvas.data()), canvas.size());
    
    arquivo.close();
    
    std::cout << "Imagem salva: " << filename << std::endl;
}