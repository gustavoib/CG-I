#include "../trabalho_final/include/Cenario.h"
#include "../trabalho_final/include/Esfera.h"
#include "../trabalho_final/include/Plano.h"
#include "../trabalho_final/include/FonteIluminacao.h"
#include "../trabalho_final/include/Janela.h"
#include "../trabalho_final/include/Camera.h"
#include "../trabalho_final/include/Ponto.h"
#include "../trabalho_final/include/Vetor.h"
#include "../trabalho_final/include/Cilindro.h"
#include "../trabalho_final/include/Cone.h"
#include "../trabalho_final/include/Cubo.h"
#include "../trabalho_final/include/Textura.h"
#include "../trabalho_final/include/Matriz.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Função para carregar código do shader de arquivo
std::string loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de shader: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

#define M_PI 3.14159265358979323846

int main() {   
    // vista padrão
    // Ponto eye(200.0f, 600.0f, 580.0f);
    // Ponto at(200.0f, 100.0f, 300.0f);
    // Vetor up(0.0f, 1.0f, 0.0f);
    // Camera* camera = new Camera(eye, at, up, 400.0f, -200.0f, 200.0f, -200.0f, 200.0f);

    // vista de cima da cena
    // Ponto eye(200.0f, 800.0f, 400.0f);
    // Ponto at(200.0f, 0.0f, 300.0f);
    // Vetor up(0.0f, 0.0f, -1.0f);
    // Camera* camera = new Camera(eye, at, up, 300.0f, -200.0f, 200.0f, -200.0f, 200.0f);

    // vista olhando para a TV
    Ponto eye(350.0f, 130.0f, 330.0f);
    Ponto at(50.0f, 110.0f, 330.0f);
    Vetor up(0.0f, 1.0f, 0.0f);
    Camera* camera = new Camera(eye, at, up, 400.0f, -200.0f, 200.0f, -200.0f, 200.0f);

    // olhar para a porta (entrada)
    // Ponto eye(200.0f, 200.0f, 200.0f);
    // Ponto at(200.0f, 80.0f, 598.0f);
    // Vetor up(0.0f, 1.0f, 0.0f);
    // Camera* camera = new Camera(eye, at, up, 400.0f, -200.0f, 200.0f, -200.0f, 200.0f);

    Cor I_F(0.65f, 0.65f, 0.65f);
    Cor I_A(0.3f, 0.3f, 0.3f);
    Ponto P_F(200.0f, 500.0f, 250.0f);
    FonteIluminacao fonte(I_F, P_F, I_A);
    
    Cor cor_background(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f);
    
    // com câmera
    Cenario cenario(camera, fonte, cor_background, 500, 500);
    
    // sem câmera
    // Cenario cenario(olho, janela, fonte, cor_background, 500, 500);
    
    //textura
    auto texturaMadeira = std::make_shared<Textura>();
    texturaMadeira->carregarImagem("../src/trabalho_final/img/textura.jpg");

    // plano de frontal (z = 0) - normal apontando para frente
    Ponto P_pif(200.0f, 200.0f, 0.0f);
    Vetor n_barf(0.0f, 0.0f, 1.0f);
    Cor kd_planof(0.686f, 0.933f, 0.933f);
    Cor ke_planof(0.686f, 0.933f, 0.933f);
    Cor ka_planof(0.686f, 0.933f, 0.933f);
    float m_planof = 50.0f;

    // lateral direita (x = 400) - normal apontando para dentro
    Ponto P_pid(400.0f, 200.0f, 200.0f);
    Vetor n_bard(-1.0f, 0.0f, 0.0f);
    Cor kd_planod(0.686f, 0.933f, 0.933f);
    Cor ke_planod(0.686f, 0.933f, 0.933f);
    Cor ka_planod(0.686f, 0.933f, 0.933f);
    float m_planod = 50.0f;

    // lateral esquerda (x = 0) - normal apontando para dentro
    Ponto P_pie(0.0f, 200.0f, 200.0f);
    Vetor n_bare(1.0f, 0.0f, 0.0f);
    Cor kd_planoe(0.686f, 0.933f, 0.933f);
    Cor ke_planoe(0.686f, 0.933f, 0.933f);
    Cor ka_planoe(0.686f, 0.933f, 0.933f);
    float m_planoe = 50.0f;

    // plano do chão (y = 0) - normal apontando para cima
    Ponto P_pic(200.0f, 0.0f, 200.0f);
    Vetor n_barc(0.0f, 1.0f, 0.0f); 
    float m_planoc = 100.0f;

    // plano do teto (y = 400) - normal apontando para baixo
    // Ponto P_pit(200.0f, 400.0f, 200.0f);
    // Vetor n_bart(0.0f, -1.0f, 0.0f); 
    // Cor kd_planot(0.933f, 0.933f, 0.933f);
    // Cor ke_planot(0.933f, 0.933f, 0.933f);
    // Cor ka_planot(0.933f, 0.933f, 0.933f);
    // float m_planot = 50.0f;

    // plano de entrada (z = 400) - normal apontando para frente
    Ponto P_pient(200.0f, 200.0f, 600.0f);
    Vetor n_barent(0.0f, 0.0f, -1.0f);
    Cor kd_planoent(0.686f, 0.933f, 0.933f);
    Cor ke_planoent(0.686f, 0.933f, 0.933f);
    Cor ka_planoent(0.686f, 0.933f, 0.933f);
    float m_planoent = 50.0f;

    Plano* plano_frontal = new Plano(n_barf, P_pif, ke_planof, kd_planof, ka_planof, m_planof);
    cenario.adicionarObjeto(plano_frontal);

    Plano* plano_chao = new Plano(n_barc, P_pic, texturaMadeira, 1.8f, 1.0f, m_planoc);
    cenario.adicionarObjeto(plano_chao);

    Plano* plano_direita = new Plano(n_bard, P_pid, ke_planod, kd_planod, ka_planod, m_planod);
    cenario.adicionarObjeto(plano_direita);

    Plano* plano_esquerda = new Plano(n_bare, P_pie, ke_planoe, kd_planoe, ka_planoe, m_planoe);
    cenario.adicionarObjeto(plano_esquerda);

    // Plano* plano_teto = new Plano(n_bart, P_pit, ke_planot, kd_planot, ka_planot, m_planot);
    // cenario.adicionarObjeto(plano_teto);

    Plano* plano_entrada = new Plano(n_barent, P_pient, ke_planoent, kd_planoent, ka_planoent, m_planoent);
    cenario.adicionarObjeto(plano_entrada);

    // mockup do cenário imaginado

    // porta de entrada (cubo)
    float aresta_porta = 80.0f;
    Ponto centro_porta(200.0f, 40.0f, 598.0f);
    Cor kd_porta(0.545f, 0.271f, 0.075f);
    Cor ke_porta(0.545f, 0.271f, 0.075f);
    Cor ka_porta(0.545f, 0.271f, 0.075f);
    float m_porta = 10.0f;
    Cubo cubo_porta;
    Malha* malha_porta = new Malha(cubo_porta.criarCubo(centro_porta, aresta_porta, ke_porta, kd_porta, ka_porta, m_porta));
    malha_porta->escalar(1.5f, 5.0f, 0.1f); // para criar a porta
    cenario.adicionarObjeto(malha_porta);

    // maçaneta da porta (esfera)
    float raio_macaneta = 5.0f;
    Ponto centro_macaneta(240.0f, 120.0f, 594.0f);
    Cor ke_macaneta(0.85f, 0.65f, 0.13f);
    Cor kd_macaneta(0.85f, 0.65f, 0.13f);
    Cor ka_macaneta(0.85f, 0.65f, 0.13f);
    float m_macaneta = 50.0f;
    Esfera* macaneta = new Esfera(raio_macaneta, centro_macaneta, ke_macaneta, kd_macaneta, ka_macaneta, m_macaneta);
    cenario.adicionarObjeto(macaneta);

    // cama
    float aresta_cubo = 80.0f;
    Ponto centro_cubo(200.0f, 5.0f, 100.0f);
    Cor kd_cubo(1.0f, 0.0f, 0.0f);
    Cor ke_cubo(1.0f, 0.0f, 0.0f);
    Cor ka_cubo(1.0f, 0.0f, 0.0f);
    float m_cubo = 10.0f;
    Cubo cubo;
    Malha* malha = new Malha(cubo.criarCubo(centro_cubo, aresta_cubo, ke_cubo, kd_cubo, ka_cubo, m_cubo));
    malha->escalar(1.3f, 0.4f, 2.5f);
    cenario.adicionarObjeto(malha);

    // travesseiro
    float aresta_travesseiro = 30.0f;
    Ponto centro_travesseiro(200.0f, 50.0f, 25.0f);
    Cor kd_travesseiro(1.0f, 1.0f, 1.0f);
    Cor ke_travesseiro(1.0f, 1.0f, 1.0f);
    Cor ka_travesseiro(1.0f, 1.0f, 1.0f);
    float m_travesseiro = 10.0f;
    Cubo cubo_travesseiro;
    Malha* malha_travesseiro = new Malha(cubo_travesseiro.criarCubo(centro_travesseiro, aresta_travesseiro, ke_travesseiro, kd_travesseiro, ka_travesseiro, m_travesseiro));
    malha_travesseiro->escalar(2.0f, 0.3f, 1.0f); // para criar o travesseiro
    cenario.adicionarObjeto(malha_travesseiro);

    // pé 1 - cama
    Ponto cb_pe1(158.0f, 0.0f, 10.0f);
    Ponto p1 = cb_pe1;
    float rb_pe1 = 5.0f;
    float H_cilindro = 40.0f;
    Vetor dc(0.0f, 1.0f, 0.0f);
    Cor kd_c(0.396f, 0.263f, 0.129f);
    Cor ke_c(0.396f, 0.263f, 0.129f);
    Cor ka_c(0.396f, 0.263f, 0.129f);
    Cilindro* pe1 = new Cilindro(p1, cb_pe1, dc, H_cilindro, rb_pe1, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe1);

    // pé 2 - cama
    Ponto cb_pe2(242.0f, 0.0f, 10.0f);
    Ponto p2 = cb_pe2;
    float rb_pe2 = 5.0f;
    Cilindro* pe2 = new Cilindro(p2, cb_pe2, dc, H_cilindro, rb_pe2, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe2);

    // pé 3 - cama
    Ponto cb_pe3(158.0f, 0.0f, 190.0f);
    Ponto p3 = cb_pe3;
    float rb_pe3 = 5.0f;
    Cilindro* pe3 = new Cilindro(p3, cb_pe3, dc, H_cilindro, rb_pe3, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe3);

    // pé 4 - cama
    Ponto cb_pe4(242.0f, 0.0f, 190.0f);
    Ponto p4 = cb_pe4;
    float rb_pe4 = 5.0f;
    Cilindro* pe4 = new Cilindro(p4, cb_pe4, dc, H_cilindro, rb_pe4, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe4);

    // mesa de cabeceira
    float aresta_mesa = 30.0f;
    Ponto centro_mesa(350.0f, 50.0f, 65.0f);
    Cor kd_mesa(0.396f, 0.263f, 0.129f);
    Cor ke_mesa(0.396f, 0.263f, 0.129f);
    Cor ka_mesa(0.396f, 0.263f, 0.129f);
    float m_mesa = 10.0f;
    Cubo cubo_mesa;
    Malha* malha_mesa = new Malha(cubo_mesa.criarCubo(centro_mesa, aresta_mesa, ke_mesa, kd_mesa, ka_mesa, m_mesa));
    malha_mesa->escalar(3.0f, 0.3f, 3.0f);
    cenario.adicionarObjeto(malha_mesa);

    // pé 1 - mesa de cabeceira
    float H_pe_mesa = 60.0f;
    Ponto cb_pe_mesa1(310.0f, 0.0f, 95.0f);
    Ponto p_pe_mesa1 = cb_pe_mesa1;
    float rb_pe_mesa = 5.0f;
    Cilindro* pe_mesa1 = new Cilindro(p_pe_mesa1, cb_pe_mesa1, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa1);

    // pé 2 - mesa de cabeceira
    Ponto cb_pe_mesa2(390.0f, 0.0f, 95.0f);
    Ponto p_pe_mesa2 = cb_pe_mesa2;
    Cilindro* pe_mesa2 = new Cilindro(p_pe_mesa2, cb_pe_mesa2, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa2);

    // pé 3 - mesa de cabeceira
    Ponto cb_pe_mesa3(310.0f, 0.0f, 35.0f);
    Ponto p_pe_mesa3 = cb_pe_mesa3;
    Cilindro* pe_mesa3 = new Cilindro(p_pe_mesa3, cb_pe_mesa3, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa3);

    // pé 4 - mesa de cabeceira
    Ponto cb_pe_mesa4(390.0f, 0.0f, 35.0f);
    Ponto p_pe_mesa4 = cb_pe_mesa4;
    Cilindro* pe_mesa4 = new Cilindro(p_pe_mesa4, cb_pe_mesa4, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa4);
    
    // arvore na mesa

    // jarro (cilindro)
    Ponto cb_jarro(350.0f, 60.0f, 65.0f);
    Ponto p_jarro = cb_jarro;
    float rb_jarro = 8.0f;
    float H_jarro_cilindro = 30.0f;
    Cor kd_jarro(0.650f, 0.200f, 0.200f);
    Cor ke_jarro(0.650f, 0.200f, 0.200f);
    Cor ka_jarro(0.650f, 0.200f, 0.200f);
    Cilindro* jarro_base = new Cilindro(p_jarro, cb_jarro, dc, H_jarro_cilindro, rb_jarro, true, true, ke_jarro, kd_jarro, ka_jarro, 10);
    cenario.adicionarObjeto(jarro_base);

    // caule (cilindro)
    Ponto cb_caule(350.0f, 74.5f, 65.0f);
    Ponto p_caule = cb_caule;
    float rb_caule = 3.0f;
    float H_caule = 30.0f;
    Cor kd_caule(0.396f, 0.263f, 0.129f);
    Cor ke_caule(0.396f, 0.263f, 0.129f);
    Cor ka_caule(0.396f, 0.263f, 0.129f);
    Cilindro* abajur_caule = new Cilindro(p_caule, cb_caule, dc, H_caule, rb_caule, false, false, ke_caule, kd_caule, ka_caule, 10);
    cenario.adicionarObjeto(abajur_caule);

    // folhas (cone)
    Ponto Cb_folhas(350.0f, 104.5f, 65.0f); // centro da base do cone
    float raio_base_cone = 15.0f;
    float H_cone = 35.0f;
    Vetor d_cone(0.0f, 1.0f, 0.0f);
    Cor kd_cone(0.0f, 0.800f, 0.200f);
    Cor ke_cone(0.0f, 0.800f, 0.200f);
    Cor ka_cone(0.0f, 0.800f, 0.200f);
    float theta = atan(raio_base_cone/H_cone);
    Ponto ponto_p_cone = Cb_folhas;
    Cone* folhas = new Cone(ponto_p_cone, Cb_folhas, d_cone, theta, H_cone, raio_base_cone, true, ke_cone, kd_cone, ka_cone, 10);
    cenario.adicionarObjeto(folhas);

    // estante na parede
    float aresta_estante = 50.0f;
    Ponto centro_estante(200.0f, 160.0f, 20.0f);
    Cor kd_estante(0.396f, 0.263f, 0.129f);
    Cor ke_estante(0.396f, 0.263f, 0.129f);
    Cor ka_estante(0.396f, 0.263f, 0.129f);
    float m_estante = 10.0f;
    Cubo cubo_estante;
    Malha* malha_estante = new Malha(cubo_estante.criarCubo(centro_estante, aresta_estante, ke_estante, kd_estante, ka_estante, m_estante));
    malha_estante->escalar(3.0f, 0.1f, 1.0f); // para criar a estante
    cenario.adicionarObjeto(malha_estante);

    // esferas decorativas na estante
    float raio_esfera = 7.0f;
    Ponto centro_esfera1(200.0f, 195.0f, 20.0f);
    Cor ke_esfera1(0.0f, 0.0f, 1.0f);
    Cor kd_esfera1(0.0f, 0.0f, 1.0f);
    Cor ka_esfera1(0.0f, 0.0f, 1.0f);
    float m_esfera1 = 10.0f;
    Esfera* esfera1 = new Esfera(raio_esfera, centro_esfera1, ke_esfera1, kd_esfera1, ka_esfera1, m_esfera1);
    cenario.adicionarObjeto(esfera1);

    Ponto centro_esfera2(150.0f, 195.0f, 20.0f);
    Cor ke_esfera2(1.0f, 1.0f, 0.0f);
    Cor kd_esfera2(1.0f, 1.0f, 0.0f);
    Cor ka_esfera2(1.0f, 1.0f, 0.0f);
    float m_esfera2 = 10.0f;
    Esfera* esfera2 = new Esfera(raio_esfera, centro_esfera2, ke_esfera2, kd_esfera2, ka_esfera2, m_esfera2);
    cenario.adicionarObjeto(esfera2);

    Ponto centro_esfera3(250.0f, 195.0f, 20.0f);
    Cor ke_esfera3(0.0f, 1.0f, 0.0f);
    Cor kd_esfera3(0.0f, 1.0f, 0.0f);
    Cor ka_esfera3(0.0f, 1.0f, 0.0f);
    float m_esfera3 = 10.0f;
    Esfera* esfera3 = new Esfera(raio_esfera, centro_esfera3, ke_esfera3, kd_esfera3, ka_esfera3, m_esfera3);
    cenario.adicionarObjeto(esfera3);

    // lixeira do outro lado da cama (cilindro)
    Ponto cb_lixeira(20.0f, 1.0f, 20.0f);
    Ponto p_lixeira = cb_lixeira;
    float rb_lixeira = 20.0f;
    float H_lixeira = 40.0f;
    Cor kd_lixeira(0.5f, 0.5f, 0.5f);
    Cor ke_lixeira(0.5f, 0.5f, 0.5f);
    Cor ka_lixeira(0.5f, 0.5f, 0.5f);
    Cilindro* lixeira = new Cilindro(p_lixeira, cb_lixeira, dc, H_lixeira, rb_lixeira, true, false, ke_lixeira, kd_lixeira, ka_lixeira, 10);
    cenario.adicionarObjeto(lixeira);

    // poltrona na parede direita
     
    // braço 1
    float aresta_braco = 40.0f;
    Ponto centro_braco1(352.0f, 15.0f, 300.0f);
    Cor kd_braco(0.7f, 0.3f, 0.4f);
    Cor ke_braco(0.7f, 0.3f, 0.4f);
    Cor ka_braco(0.7f, 0.3f, 0.4f);
    float m_braco = 10.0f;
    Cubo cubo_braco1;
    Malha* malha_braco1 = new Malha(cubo_braco1.criarCubo(centro_braco1, aresta_braco, ke_braco, kd_braco, ka_braco, m_braco));
    malha_braco1->escalar(2.4f, 3.0f, 0.8f);
    cenario.adicionarObjeto(malha_braco1);
    
    // braço 2
    Ponto centro_braco2(352.0f, 15.0f, 500.0f);
    Cubo cubo_braco2;
    Malha* malha_braco2 = new Malha(cubo_braco2.criarCubo(centro_braco2, aresta_braco, ke_braco, kd_braco, ka_braco, m_braco));
    malha_braco2->escalar(2.4f, 3.0f, 0.8f);
    cenario.adicionarObjeto(malha_braco2);
    
    // assento
    Ponto centro_assento(400.0f, 10.0f, 400.0f);
    float aresta_assento = 60.0f;
    Cubo cubo_assento;
    Malha* malha_assento = new Malha(cubo_assento.criarCubo(centro_assento, aresta_assento, ke_braco, kd_braco, ka_braco, m_braco));
    malha_assento->escalar(3.0f, 0.5f, 3.0f);
    cenario.adicionarObjeto(malha_assento);

    // encosto
    Ponto centro_encosto(400.0f, 10.0f, 400.0f);
    float aresta_encosto = 60.0f;
    Cubo cubo_encosto;
    Malha* malha_encosto = new Malha(cubo_encosto.criarCubo(centro_encosto, aresta_encosto, ke_braco, kd_braco, ka_braco, m_braco));
    malha_encosto->escalar(0.7f, 3.0f, 3.0f);
    cenario.adicionarObjeto(malha_encosto);

    // mesa na parede oposta ao sofá
    float aresta_mesa_parede = 40.0f;
    Ponto centro_mesa_parede(50.0f, 80.0f, 400.0f);
    Cor kd_mesa_parede(0.396f, 0.263f, 0.129f);
    Cor ke_mesa_parede(0.396f, 0.263f, 0.129f);
    Cor ka_mesa_parede(0.396f, 0.263f, 0.129f);
    float m_mesa_parede = 10.0f;
    Cubo cubo_mesa_parede;
    Malha* malha_mesa_parede = new Malha(cubo_mesa_parede.criarCubo(centro_mesa_parede, aresta_mesa_parede, ke_mesa_parede, kd_mesa_parede, ka_mesa_parede, m_mesa_parede));
    malha_mesa_parede->escalar(3.0f, 0.5f, 5.0f);
    cenario.adicionarObjeto(malha_mesa_parede);

    // suporte 1 pra mesa oposta ao sofá
    Ponto cb_suporte1(30.0f, 0.0f, 380.0f);
    Ponto p_suporte1 = cb_suporte1;
    float rb_suporte = 5.0f;
    float H_suporte = 90.0f;
    Cilindro* suporte1 = new Cilindro(p_suporte1, cb_suporte1, dc, H_suporte, rb_suporte, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(suporte1);

    // suporte 2 pra mesa oposta ao sofá
    Ponto cb_suporte2(70.0f, 0.0f, 380.0f);
    Ponto p_suporte2 = cb_suporte2;
    Cilindro* suporte2 = new Cilindro(p_suporte2, cb_suporte2, dc, H_suporte, rb_suporte, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(suporte2);
    
    // suporte 3 pra mesa oposta ao sofá
    Ponto cb_suporte3(30.0f, 0.0f, 420.0f);
    Ponto p_suporte3 = cb_suporte3;
    Cilindro* suporte3 = new Cilindro(p_suporte3, cb_suporte3, dc, H_suporte, rb_suporte, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(suporte3);
    
    // suporte 4 pra mesa oposta ao sofá
    Ponto cb_suporte4(70.0f, 0.0f, 420.0f);
    Ponto p_suporte4 = cb_suporte4;
    Cilindro* suporte4 = new Cilindro(p_suporte4, cb_suporte4, dc, H_suporte, rb_suporte, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(suporte4);

    // tv em cima da mesa
    float aresta_tv = 40.0f;
    Ponto centro_tv(40.0f, 110.0f, 400.0f);
    Cor kd_tv(0.8f, 0.8f, 0.8f);
    Cor ke_tv(0.8f, 0.8f, 0.8f);
    Cor ka_tv(0.8f, 0.8f, 0.8f);
    float m_tv = 10.0f;
    Cubo cubo_tv;
    Malha* malha_tv = new Malha(cubo_tv.criarCubo(centro_tv, aresta_tv, ke_tv, kd_tv, ka_tv, m_tv));
    malha_tv->escalar(1.0f, 1.5f, 1.5f);
    cenario.adicionarObjeto(malha_tv);

    float aresta_tv2 = 40.0f;
    Ponto centro_tv2(50.0f, 110.0f, 400.0f);
    Cor kd_tv2(0.8f, 0.8f, 0.8f);
    Cor ke_tv2(0.8f, 0.8f, 0.8f);
    Cor ka_tv2(0.8f, 0.8f, 0.8f);
    float m_tv2 = 10.0f;
    Cubo cubo_tv2;
    Malha* malha_tv2 = new Malha(cubo_tv2.criarCubo(centro_tv2, aresta_tv2, ke_tv2, kd_tv2, ka_tv2, m_tv2));
    malha_tv2->escalar(1.0f, 2.0f, 2.0f);
    cenario.adicionarObjeto(malha_tv2);

    // tela da tv
    float aresta_tela = 40.0f;
    Ponto centro_tela(69.0f, 120.0f, 400.0f);
    Cor kd_tela(0.1f, 0.3f, 0.6f);
    Cor ke_tela(0.1f, 0.3f, 0.6f);
    Cor ka_tela(0.1f, 0.3f, 0.6f);
    float m_tela = 10.0f;
    Cubo cubo_tela;
    Malha* malha_tela = new Malha(cubo_tela.criarCubo(centro_tela, aresta_tela, ke_tela, kd_tela, ka_tela, m_tela));
    malha_tela->escalar(0.1f, 1.0f, 1.5f);
    cenario.adicionarObjeto(malha_tela);

    // antenas da tv
    Ponto cb_antena1(50.0f, 155.0f, 395.0f);
    Ponto p_antena1 = cb_antena1;
    float rb_antena = 2.0f;
    float H_antena = 50.0f;
    Cor kd_ant(0.3f, 0.3f, 0.3f);
    Cor ke_ant(0.3f, 0.3f, 0.3f);
    Cor ka_ant(0.3f, 0.3f, 0.3f);
    Cilindro* antena1 = new Cilindro(p_antena1, cb_antena1, dc, H_antena, rb_antena, false, false, ke_ant, kd_ant, ka_ant, 10);
    antena1->rotacionarX(-30.0f);
    cenario.adicionarObjeto(antena1);

    Ponto cb_antena2(50.0f, 155.0f, 405.0f);
    Ponto p_antena2 = cb_antena2;
    Cilindro* antena2 = new Cilindro(p_antena2, cb_antena2, dc, H_antena, rb_antena, false, false, ke_ant, kd_ant, ka_ant, 10);
    antena2->rotacionarX(30.0f);
    cenario.adicionarObjeto(antena2);

    // frigobar ao lado da mesa de parede
    float aresta_frigobar = 50.0f;
    Ponto centro_frigobar(33.0f, 0.0f, 262.0f);
    Cor kd_frigobar(0.915f, 0.915f, 0.915f);
    Cor ke_frigobar(0.915f, 0.915f, 0.915f);
    Cor ka_frigobar(0.915f, 0.915f, 0.915f);
    float m_frigobar = 10.0f;
    Cubo cubo_frigobar;
    Malha* malha_frigobar = new Malha(cubo_frigobar.criarCubo(centro_frigobar, aresta_frigobar, ke_frigobar, kd_frigobar, ka_frigobar, m_frigobar));
    malha_frigobar->escalar(1.5f, 3.5f, 1.2f);
    cenario.adicionarObjeto(malha_frigobar);

    // puxador da porta do frigobar (cilindro)
    Ponto cb_puxador(70.0f, 60.0f, 280.0f);
    Ponto p_puxador = cb_puxador;
    float rb_puxador = 3.0f;
    float H_puxador = 20.0f;
    Cor kd_puxador(0.0f, 0.0f, 0.0f);
    Cor ke_puxador(0.0f, 0.0f, 0.0f);
    Cor ka_puxador(0.0f, 0.0f, 0.0f);
    Cilindro* puxador = new Cilindro(p_puxador, cb_puxador, dc, H_puxador, rb_puxador, true, true, ke_puxador, kd_puxador, ka_puxador, 10);
    cenario.adicionarObjeto(puxador);

    /*
    // esfera
    // float raio_esfera = 5.0f;
    // Ponto centro_esfera(0.0f, 95.0f, -200.0f);
    // Cor ke_esfera(0.854f, 0.647f, 0.125f);
    // Cor kd_esfera(0.854f, 0.647f, 0.125f);
    // Cor ka_esfera(0.854f, 0.647f, 0.125f);
    // float m_esfera = 10.0f;
    
    // Esfera* esfera = new Esfera(raio_esfera, centro_esfera, ke_esfera, kd_esfera, ka_esfera, m_esfera);
    // cenario.adicionarObjeto(esfera);

    // cilindro
    // Ponto centro_base(0.0f, -150.0f, -200.0f);
    // Ponto ponto_p = centro_base;
    // float raio_base = 5.0f;
    // float H_cilindro = 90.0f;
    // Vetor dc(0.0f, 1.0f, 0.0f);
    // Cor kd_c(0.824f, 0.706f, 0.549f);
    // Cor ke_c(0.824f, 0.706f, 0.549f);
    // Cor ka_c(0.824f, 0.706f, 0.549f);

    // Cilindro* cilindro = new Cilindro(ponto_p, centro_base, dc, H_cilindro, raio_base, false, false, ke_c, kd_c, ka_c, 10);
    // cenario.adicionarObjeto(cilindro);

    // cone
    // Ponto Cb(0.0f, -60.0f, -200.0f); // centro da base do cone
    // float raio_base_cone = 90.0f;
    // float H_cone = 150.0f;
    // Vetor d_cone(0.0f, 1.0f, 0.0f);
    // Cor kd_cone(0.0f, 1.0f, 0.498f);
    // Cor ke_cone(0.0f, 1.0f, 0.498f);
    // Cor ka_cone(0.0f, 1.0f, 0.498f);
    // float theta = atan(raio_base_cone/H_cone);
    // Ponto ponto_p_cone = Cb;

    // Cone* cone = new Cone(ponto_p_cone, Cb, d_cone, theta, H_cone, raio_base_cone, false, ke_cone, kd_cone, ka_cone, 10);
    // cenario.adicionarObjeto(cone);

    // cubo
    // float aresta_cubo = 40.0f;
    // Ponto centro_cubo(0.0f, -150.0f, -165.0f);
    // Cor kd_cubo(1.0f, 0.078f, 0.576f);
    // Cor ke_cubo(1.0f, 0.078f, 0.576f);
    // Cor ka_cubo(1.0f, 0.078f, 0.576f);
    // float m_cubo = 10.0f;

    // Cubo cubo;
    // Malha* malha = new Malha(cubo.criarCubo(centro_cubo, aresta_cubo, ke_cubo, kd_cubo, ka_cubo, m_cubo));
    // cenario.adicionarObjeto(malha);*/

    // renderizar a cena (preenche o canvas)
    cenario.render();


    // GLFW ----------------------------------------------------------------------------------------------------------------------------
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }

    // criar janela GLFW
    GLFWwindow* window = glfwCreateWindow(cenario.n_col, cenario.n_lin, "Trabalho final CG", NULL, NULL);
    if (!window) {
        std::cerr << "Falha ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    // compilar shaders
    std::string vertexShaderSource = loadShaderSource("../src/trabalho_final/shaders/vertex_shader.glsl");
    std::string fragmentShaderSource = loadShaderSource("../src/trabalho_final/shaders/fragment_shader.glsl");

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vss = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fss = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fss, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -1.0f,  1.0f, 0.0f, 0.0f,  // Superior esquerdo -> TexCoord 0,0
        -1.0f, -1.0f, 0.0f, 1.0f,  // Inferior esquerdo -> TexCoord 0,1
         1.0f, -1.0f, 1.0f, 1.0f,  // Inferior direito -> TexCoord 1,1
        -1.0f,  1.0f, 0.0f, 0.0f,  // Superior esquerdo -> TexCoord 0,0
         1.0f, -1.0f, 1.0f, 1.0f,  // Inferior direito -> TexCoord 1,1
         1.0f,  1.0f, 1.0f, 0.0f   // Superior direito -> TexCoord 1,0
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // criar textura
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cenario.n_col, cenario.n_lin, 0, GL_RGB, GL_UNSIGNED_BYTE, cenario.canvas.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // manter janela aberta até o usuário fechá-la
    while (!glfwWindowShouldClose(window)) {
        // processar entrada
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // renderizar
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // limpar
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    glfwTerminate();


    // Liberar memória
    // delete esfera;
    delete plano_frontal;
    delete plano_chao;
    delete plano_entrada;
    delete plano_direita;
    delete plano_esquerda;
    // delete plano_teto;
    // delete cilindro;
    // delete cone;
    // delete malha;
    delete camera; // quando não usar, apagar daqui
   
    return 0;
}