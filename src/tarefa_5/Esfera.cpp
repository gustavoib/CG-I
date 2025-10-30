#include "Esfera.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

Esfera::Esfera(float raio, Ponto& centro, Cor& ke, Cor& kd, Cor& ka, float m) : ObjetoAbstrato(ke, kd, ka, m), raio_esfera(raio), centro_esfera(centro) {}

bool Esfera::intersecao(Raio& raio, float& t) {
    Vetor w = raio.origem.subPonto(centro_esfera);
    Vetor d = raio.direcao;

    float a = d.produtoEscalar(d);
    float b = 2.0f * w.produtoEscalar(d);
    float c = w.produtoEscalar(w) - raio_esfera*raio_esfera;

    float delta = b*b - 4*a *c;

    if (delta >= 0) {
        float t1 = (-b - sqrt(delta))/(2.0f*a);
        float t2 = (-b + sqrt(delta))/(2.0f*a);
        t = min(t1, t2);
        
        return true;
    }
    
    return false;
}

Cor Esfera::calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
    Vetor n = Pi.subPonto(centro_esfera).normalizado();

    Vetor P_F_minus_Pi = fonte.P_F.subPonto(Pi);
    Vetor l = P_F_minus_Pi.normalizado();

    Vetor v = direcao_raio.vetorNegativo();

    float produto_nl = n.produtoEscalar(l);
    Vetor r = n.multiEscalar(2.0f * produto_nl).subVetor(l);

    // continuar nos ks da esfera
    Cor IFKd = fonte.I_F.multiComponente(Kd);
    Cor IFKe = fonte.I_F.multiComponente(Ke);

    float produto_nl_limitado = max(0.0f, n.produtoEscalar(l));
    Cor I_d = IFKd.multiEscalar(produto_nl_limitado);
   
    float produto_vr_limitado = max(0.0f, v.produtoEscalar(r));
    float vrm = pow(produto_vr_limitado, this->m);
    Cor I_e = IFKe.multiEscalar(vrm);

    Cor I_a = fonte.I_A.multiComponente(Ka);

    Cor IdIe = I_d.somarCor(I_e);
    Cor IE = IdIe.somarCor(I_a);
    IE.limitar();

    return IE;

}