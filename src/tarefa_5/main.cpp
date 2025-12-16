#include "../tarefa_5/include/Cenario.h"
#include "../tarefa_5/include/Esfera.h"
#include "../tarefa_5/include/Plano.h"
#include "../tarefa_5/include/FonteIluminacao.h"
#include "../tarefa_5/include/Janela.h"
#include "../tarefa_5/include/Ponto.h"
#include "../tarefa_5/include/Vetor.h"
#include "../tarefa_5/include/Cilindro.h"
#include "../tarefa_5/include/Cone.h"
#include "../tarefa_5/include/Cubo.h"
#include "../tarefa_5/include/Textura.h"
#include <cmath>
#include <iostream>
#include <memory>

#define M_PI 3.14159265358979323846

int main() {
    Ponto olho(0.0f, 0.0f, -5.0f);
    Janela janela(60.0f, 60.0f, -30.0f); 
    Cor I_F(0.7f, 0.7f, 0.7f);
    Cor I_A(0.3f, 0.3f, 0.3f);
    Ponto P_F(-100.0f, 140.0f, -20.0f);
    FonteIluminacao fonte(I_F, P_F, I_A);
    float raio_esfera = 5.0f;
    
    Cor cor_background(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f);
    
    Cenario cenario(olho, janela, fonte, cor_background, 500, 500);
    
    //textura
    auto texturaMadeira = std::make_shared<Textura>();
    texturaMadeira->carregarImagem("textura.jpg");
    
    // esfera
    Ponto centro_esfera(0.0f, 95.0f, -200.0f);
    Cor ke_esfera(0.854f, 0.647f, 0.125f);
    Cor kd_esfera(0.854f, 0.647f, 0.125f);
    Cor ka_esfera(0.854f, 0.647f, 0.125f);
    float m_esfera = 10.0f;
    
    Esfera* esfera = new Esfera(raio_esfera, centro_esfera, ke_esfera, kd_esfera, ka_esfera, m_esfera);
    cenario.adicionarObjeto(esfera);

    // plano de frontal
    Ponto P_pif(200.0f, 150.0f, -400.0f);
    Vetor n_barf(0.0f, 0.0f, 1.0f);  // Normal apontando para cima
    Cor kd_planof(0.686f, 0.933f, 0.933f);
    Cor ke_planof(0.686f, 0.933f, 0.933f);
    Cor ka_planof(0.686f, 0.933f, 0.933f);
    float m_planof = 10.0f;

    // lateral direita
    Ponto P_pid(200.0f, -150.0f, 0.0f);
    Vetor n_bard(-1.0f, 0.0f, 0.0f);  // Normal apontando para cima
    Cor kd_planod(0.686f, 0.933f, 0.933f);
    Cor ke_planod(0.686f, 0.933f, 0.933f);
    Cor ka_planod(0.686f, 0.933f, 0.933f);
    float m_planod = 10.0f;

    // lateral esquerda
    Ponto P_pie(-200.0f, -150.0f, 0.0f);
    Vetor n_bare(1.0f, 0.0f, 0.0f);  // Normal apontando para cima
    Cor kd_planoe(0.686f, 0.933f, 0.933f);
    Cor ke_planoe(0.686f, 0.933f, 0.933f);
    Cor ka_planoe(0.686f, 0.933f, 0.933f);
    float m_planoe = 10.0f;

    // plano do chão
    Ponto P_pic(0.0f, -150.0f, 0.0f);
    Vetor n_barc(0.0f, 1.0f, 0.0f); 
    float m_planoc = 10.0f;

    // plano do teto
    Ponto P_pit(0.0f, 150.0f, 0.0f);
    Vetor n_bart(0.0f, -1.0f, 0.0f); 
    Cor kd_planot(0.933f, 0.933f, 0.933f);
    Cor ke_planot(0.933f, 0.933f, 0.933f);
    Cor ka_planot(0.933f, 0.933f, 0.933f);
    float m_planot = 10.0f;

    Plano* plano_frontal = new Plano(n_barf, P_pif, ke_planof, kd_planof, ka_planof, m_planof);
    cenario.adicionarObjeto(plano_frontal);

    Plano* plano_chao = new Plano(n_barc, P_pic, texturaMadeira, 0.2f, 0.2f, m_planoc);
    cenario.adicionarObjeto(plano_chao);

    Plano* plano_direita = new Plano(n_bard, P_pid, ke_planod, kd_planod, ka_planod, m_planod);
    cenario.adicionarObjeto(plano_direita);

    Plano* plano_esquerda = new Plano(n_bare, P_pie, ke_planoe, kd_planoe, ka_planoe, m_planoe);
    cenario.adicionarObjeto(plano_esquerda);

    Plano* plano_teto = new Plano(n_bart, P_pit, ke_planot, kd_planot, ka_planot, m_planot);
    cenario.adicionarObjeto(plano_teto);

    // cilindro
    Ponto centro_base(0.0f, -150.0f, -200.0f);
    Ponto ponto_p = centro_base;
    float raio_base = 5.0f;
    float H_cilindro = 90.0f;
    Vetor dc(0.0f, 1.0f, 0.0f); // vetor normal (n ou u ou dc)
    Cor kd_c(0.824f, 0.706f, 0.549f);
    Cor ke_c(0.824f, 0.706f, 0.549f);
    Cor ka_c(0.824f, 0.706f, 0.549f);

    Cilindro* cilindro = new Cilindro(ponto_p, centro_base, dc, H_cilindro, raio_base, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(cilindro);

    // cone
    Ponto Cb(0.0f, -60.0f, -200.0f); // centro da base do cone
    float raio_base_cone = 90.0f;
    float H_cone = 150.0f;
    Vetor d_cone(0.0f, 1.0f, 0.0f);
    Cor kd_cone(0.0f, 1.0f, 0.498f);
    Cor ke_cone(0.0f, 1.0f, 0.498f);
    Cor ka_cone(0.0f, 1.0f, 0.498f);
    float theta = atan(raio_base_cone/H_cone);
    Ponto ponto_p_cone = Cb;

    Cone* cone = new Cone(ponto_p_cone, Cb, d_cone, theta, H_cone, raio_base_cone, false, ke_cone, kd_cone, ka_cone, 10);
    cenario.adicionarObjeto(cone);

    // cubo
    float aresta_cubo = 40.0f;
    Ponto centro_cubo(0.0f, -150.0f, -165.0f);
    Cor kd_cubo(1.0f, 0.078f, 0.576f);
    Cor ke_cubo(1.0f, 0.078f, 0.576f);
    Cor ka_cubo(1.0f, 0.078f, 0.576f);
    float m_cubo = 10.0f;

    Cubo cubo;
    Malha* malha = new Malha(cubo.criarCubo(centro_cubo, aresta_cubo, ke_cubo, kd_cubo, ka_cubo, m_cubo));
    cenario.adicionarObjeto(malha);

    cenario.render();
    cenario.salvarPPM("tarefa_5.ppm");
    
    // Liberar memória
    delete esfera;
    delete plano_frontal;
    delete plano_chao;
    delete plano_direita;
    delete plano_esquerda;
    delete plano_teto;
    delete cilindro;
    delete cone;
    delete malha;
    
    return 0;
}