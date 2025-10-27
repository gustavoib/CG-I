#include "Cone.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cfloat>

using namespace std;

Cone::Cone(Ponto& P, Ponto& V, Vetor& n, float theta, float H, float R, Cor& ke, Cor& kd, Cor& ka, float m)
:ObjetoAbstrato(ke, kd, ka, m), P(P), V(V), n(n), H(H), R(R) {};

bool Cone::intersecao(Raio& raio, float& t) {
    Vetor VmenosP = V.subPonto(raio.origem);
    // Removida a linha: float VPdotn = VmenosP.produtoEscalar(n);

    float dn = raio.direcao.produtoEscalar(n);
    float vd = VmenosP.produtoEscalar(raio.direcao);
    float vn = VmenosP.produtoEscalar(n);
    float dn_quadrado = dn*dn;
    float d_quadrado = raio.direcao.produtoEscalar(raio.direcao);
    float cos_quadrado = pow(cos(theta), 2);
    float dd_cosseno = d_quadrado*(cos_quadrado);

    float a = dn_quadrado-dd_cosseno;
    float b = (vd*cos_quadrado)-(vn*dn);
    float c = (vn*vn) - (VmenosP.produtoEscalar(VmenosP))*cos_quadrado;

    float tEscolhido = FLT_MAX;
    bool temIntersecao = false;
    
    float delta = b*b - 4*a*c;

    if (delta >= 0) {
        float t1 = (-b - sqrt(delta))/(2.0f*a);
        float t2 = (-b + sqrt(delta))/(2.0f*a);

        for (float ti : {t1, t2}) {
            if (ti > 0) {
                Ponto p = raio.equacaoRaio(ti);
                float VmenosPdotn = (V.subPonto(p)).produtoEscalar(n);

                if (VmenosPdotn >= 0 && VmenosPdotn <= H) {
                    temIntersecao = true;
                    tEscolhido = min(tEscolhido, ti);
                }
            }
        }
    }

    if (temIntersecao) {
        t = tEscolhido;
        return true;
    }
    
    return false;
}

Cor Cone::calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
    Vetor Pi_V = Pi.subPonto(V);                
    float proj = Pi_V.produtoEscalar(n);        
    Vetor P_proj = n.multiEscalar(proj);        
    Vetor radial = Pi_V.subVetor(P_proj);
    
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    
    // Corrigido: criar vetores temporários para evitar problemas de referência
    Vetor radial_norm = radial.normalizado();
    Vetor parte_radial = radial_norm.multiEscalar(cos_theta);
    Vetor parte_axial = n.multiEscalar(-sin_theta);
    Vetor normal_cone = parte_radial.somarVetor(parte_axial);
    Vetor normal = normal_cone.normalizado();

    Vetor P_F_minus_Pi = fonte.P_F.subPonto(Pi);
    Vetor l = P_F_minus_Pi.normalizado();

    Vetor v = direcao_raio.vetorNegativo();

    float produto_nl = normal.produtoEscalar(l);
    Vetor r = normal.multiEscalar(2.0f * produto_nl).subVetor(l);

    Cor IFKd = fonte.I_F.multiComponente(Kd);
    Cor IFKe = fonte.I_F.multiComponente(Ke);
    Cor I_a = fonte.I_A.multiComponente(Ka);

    float produto_nl_limitado = max(0.0f, produto_nl);
    Cor I_d = IFKd.multiEscalar(produto_nl_limitado);

    float produto_vr_limitado = max(0.0f, v.produtoEscalar(r));
    float vrm = pow(produto_vr_limitado, this->m);
    Cor I_e = IFKe.multiEscalar(vrm);

    Cor IdIe = I_d.somarCor(I_e);
    Cor IE = IdIe.somarCor(I_a);
    IE.limitar();

    return IE;
}