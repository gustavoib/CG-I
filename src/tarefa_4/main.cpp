#include "Cenario.h"
#include "Esfera.h"
#include "Plano.h"
#include "FonteIluminacao.h"
#include "Janela.h"
#include "Ponto.h"
#include "Vetor.h"
#include "Cilindro.h"
#include "Cone.h"
#include <cmath>

#define M_PI 3.14159265358979323846

int main() {
    Ponto olho(0.0f, 0.0f, 0.0f);
    Janela janela(60.0f, 60.0f, -30.0f); 
    Cor I_F(0.7f, 0.7f, 0.7f);
    Cor I_A(0.3f, 0.3f, 0.3f);
    Ponto P_F(0.0f, 60.0f, -30.0f);
    FonteIluminacao fonte(I_F, P_F, I_A);
    float raio_esfera = 40;
    
    Cor cor_background(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f);
    
    Cenario cenario(olho, janela, fonte, cor_background, 500, 500);
    
    // esfera
    Ponto centro_esfera(0.0f, 0.0f, -100.0f);
    Cor ke_esfera(0.7f, 0.2f, 0.2f);
    Cor kd_esfera(0.7f, 0.2f, 0.2f);
    Cor ka_esfera(0.7f, 0.2f, 0.2f);
    float m_esfera = 10.0f;
    
    Esfera* esfera = new Esfera(raio_esfera, centro_esfera, ke_esfera, kd_esfera, ka_esfera, m_esfera);
    cenario.adicionarObjeto(esfera);

    // plano de fundo
    Ponto P_pif(0.0f, 0.0f, -200.0f);
    Vetor n_barf(0.0f, 0.0f, 1.0f);  // Normal apontando para cima
    Cor kd_planof(0.3, 0.3, 0.7);
    Cor ke_planof(0.0f, 0.0f, 0.0f);
    Cor ka_planof(0.3, 0.3, 0.7);
    float m_planof = 1.0f;

    // plano do chão
    Ponto P_pic(0.0f, -raio_esfera, 0.0f);
    Vetor n_barc(0.0f, 1.0f, 0.0f); 
    Cor kd_planoc(0.2, 0.7f, 0.2f);
    Cor ke_planoc(0.0f, 0.0f, 0.0f);
    Cor ka_planoc(0.2f, 0.7f, 0.2f);
    float m_planoc = 1.0f;

    Plano* plano_fundo = new Plano(n_barf, P_pif, ke_planof, kd_planof, ka_planof, m_planof);
    cenario.adicionarObjeto(plano_fundo);

    Plano* plano_chao = new Plano(n_barc, P_pic, ke_planoc, kd_planoc, ka_planoc, m_planoc);
    cenario.adicionarObjeto(plano_chao);

    // cilindro
    Ponto centro_base(0.0f, 0.0f, -100.0f);
    Ponto ponto_p(0.0f, 0.0f, -100.0f);
    float raio_base = raio_esfera/3.0f;
    float H_cilindro = 3.0f * raio_esfera;
    Vetor dc(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
    Cor kd_c(0.2, 0.3f, 0.8f);
    Cor ke_c(0.2, 0.3f, 0.8f);
    Cor ka_c(0.2, 0.3f, 0.8f);

    // (Ponto& P, Ponto& B, Vetor& u, float H, float R, Cor& ke, Cor& kd, Cor& ka, float m)
    Cilindro* cilindro = new Cilindro(ponto_p, centro_base, dc, H_cilindro, raio_base, true, true, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(cilindro);

    // cone
    Ponto Cb = centro_base.somarVetor(dc.multiEscalar(H_cilindro)); // centro da base do cone
    float raio_base_cone = 1.5f * raio_esfera;
    float H_cone = (1.0f/3.0f) * raio_base_cone;
    Vetor d_cone(-1/sqrt(3), 1/sqrt(3), -1/sqrt(3));
    Cor kd_cone(0.8f, 0.3f, 0.2f);
    Cor ke_cone(0.8f, 0.3f, 0.2f);
    Cor ka_cone(0.8f, 0.3f, 0.2f);
    float theta = atan(raio_base_cone/H_cone);
    Ponto ponto_p_cone = Cb;

    Cone* cone = new Cone(ponto_p_cone, Cb, d_cone, theta, H_cone, raio_base_cone, true, ke_cone, kd_cone, ka_cone, 10);
    cenario.adicionarObjeto(cone);

    cenario.render();
    cenario.salvarPPM("tarefa_4.ppm");
    
    // Liberar memória
    delete esfera;
    delete plano_fundo;
    delete plano_chao;
    delete cilindro;
    delete cone;
    
    return 0;
}