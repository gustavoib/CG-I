#include "Cone.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cfloat>

using namespace std;

Cone::Cone(Ponto& P, Ponto& Cb, Vetor& n, float theta, float H, float R, Cor& ke, Cor& kd, Cor& ka, float m)
:ObjetoAbstrato(ke, kd, ka, m), P(P), Cb(Cb), n(n), theta(theta), H(H), R(R) {};

bool Cone::intersecao(Raio& raio, float& t) {
    Ponto V = Cb.somarVetor(n.multiEscalar(H)); // vértice do cone
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

    if (a == 0 && b != 0) {
        float t = -c/(2.0f * b);
        
        if (t > 0.0001f) {
            Ponto Pi = raio.equacaoRaio(t);
            float VmenosPdotn = (V.subPonto(Pi)).produtoEscalar(n);
            if (VmenosPdotn >= 0 && VmenosPdotn <= H) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, t);
            }
        }
    }

    float delta = b*b - a*c;

    if (delta >= 0) {
        float t1 = (-b - sqrt(delta))/(a);
        float t2 = (-b + sqrt(delta))/(a);

        for (float ti : {t1, t2}) {
            if (ti > 0.0001f) {
                Ponto p = raio.equacaoRaio(ti);
                float VmenosPdotn = (V.subPonto(p)).produtoEscalar(n);

                if (VmenosPdotn >= 0 && VmenosPdotn <= H) {
                    temIntersecao = true;
                    tEscolhido = min(tEscolhido, ti);
                }
            }
        }
    }

    if (dn != 0) {
        Vetor v_base = raio.origem.subPonto(Cb);
        float t_base = -(v_base.produtoEscalar(n)/ dn);
        
        if (t_base > 0.0001f) {
            Ponto p_base = raio.equacaoRaio(t_base);
            Vetor dist_centro = p_base.subPonto(Cb);
            float dist_quadrada = dist_centro.produtoEscalar(dist_centro);
            
            if (dist_quadrada <= R*R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, t_base);
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
    Ponto vertice = Cb.somarVetor(n.multiEscalar(H));
    Vetor Pi_Cb = Pi.subPonto(Cb);
    float proj = Pi_Cb.produtoEscalar(n);
    
    Vetor normal;
    // calcular normal da base
    if (proj < 0.0001f) {
        normal = n.vetorNegativo();
    } 
    // calcular normal da superfície lateral
    else {
        Vetor Pi_V = Pi.subPonto(vertice);
        float dist_ao_vertice = Pi_V.norma();
        
        if (dist_ao_vertice < 0.0001f) {
            normal = n;
        } else {
            float PiV_dot_n = Pi_V.produtoEscalar(n);
            float cos_theta = cos(theta);
            float cos_theta_sq = cos_theta * cos_theta;
            
            Vetor termo = n.multiEscalar(PiV_dot_n / cos_theta_sq);
            normal = Pi_V.subVetor(termo).normalizado();
        }
    }

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