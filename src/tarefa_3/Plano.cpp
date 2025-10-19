// Plano.cpp
#include "Plano.h"
#include <cmath>
#include <algorithm>

using namespace std;

Plano::Plano(Vetor& n, Ponto& p, Cor& ke, Cor& kd, Cor& ka, float m) 
    : ObjetoAbstrato(ke, kd, ka, m), n(n.normalizado()), P_pi(p) {}

bool Plano::intersecao(Raio& raio, float& t) {
    float denominador = n.produtoEscalar(raio.direcao);
    
    if (fabs(denominador) == 0) {
        return false;
    }
    
    Vetor w = raio.origem.subPonto(P_pi);
    t = -w.produtoEscalar(n) / denominador;

    if (t > 0) {
        return true;
    } else {
        return false;
    }
}

Cor Plano::calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
    Vetor vetor_n = n;
    
    Vetor v = direcao_raio.vetorNegativo();
    
    Vetor l = fonte.P_F.subPonto(Pi).normalizado();
    
    float produto_nl_limitado = max(0.0f, vetor_n.produtoEscalar(l));
    Vetor r = vetor_n.multiEscalar(2.0f * produto_nl_limitado).subVetor(l);
    
    Cor IFKd = fonte.I_F.multiComponente(Kd);
    Cor I_d = IFKd.multiEscalar(produto_nl_limitado);

    Cor IFKe = fonte.I_F.multiComponente(Ke);    
    float produto_vr = max(0.0f, v.produtoEscalar(r));
    Cor I_e = IFKe.multiEscalar(pow(produto_vr, this->m));

    Cor I_a = fonte.I_A.multiComponente(Ka);
    
    Cor IdIe = I_d.somarCor(I_e);
    Cor IE = IdIe.somarCor(I_a);
    
    IE.limitar();
    
    return IE;
}