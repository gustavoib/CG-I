#include "Cilindro.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cfloat>

using namespace std;

Cilindro::Cilindro(Ponto& P, Ponto& B, Vetor& u, float H, float R, Cor& ke, Cor& kd, Cor& ka, float m)
: ObjetoAbstrato(ke, kd, ka, m), P(P), B(B), u(u), H(H), R(R) {};

bool Cilindro::intersecao(Raio& raio, float& t) {
    Vetor PmenosB = raio.origem.subPonto(B);
    float PBdotu = PmenosB.produtoEscalar(u);
    Vetor PBuu = u.multiEscalar(PBdotu);
    Vetor v = PmenosB.subVetor(PBuu);

    float du = raio.direcao.produtoEscalar(u);
    Vetor duu = u.multiEscalar(du);
    Vetor w = raio.direcao.subVetor(duu);

    float a = w.produtoEscalar(w);
    float b = 2*(v.produtoEscalar(w));
    float c = v.produtoEscalar(v) - R*R;

    float tEscolhido = FLT_MAX;
    bool temIntersecao = false;
    
    Vetor uH = u.multiEscalar(H);
    Ponto T = B.somarVetor(uH);

    // aqui vai ser especifico pro a = 0
    if (a == 0) {
        Vetor wB = raio.origem.subPonto(B);
        Vetor wT = raio.origem.subPonto(T);

        if (du == 0) {
            return false;
        }

        float ttopo = -(wT.produtoEscalar(u)/du);
        float tbase = -(wB.produtoEscalar(u)/du);

        if (tbase > 0.0001f) {
            Ponto Pibase = raio.equacaoRaio(tbase);
            float distBase = (Pibase.subPonto(B)).norma();
            if (distBase <= R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, tbase);
            }
        }

        if (ttopo > 0.0001f) {
            Ponto Pitopo = raio.equacaoRaio(ttopo);
            float distTopo = (Pitopo.subPonto(T)).norma();
            if (distTopo <= R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, ttopo);
            }
        }

        if (temIntersecao) {
            t = tEscolhido;
            return true;
        }
        
        return false;
    }

    float delta = b*b - 4*a*c;

    if (delta >= 0) {
        float t1 = (-b - sqrt(delta))/(2.0f*a);
        float t2 = (-b + sqrt(delta))/(2.0f*a);

        for (float ti : {t1, t2}) {
            if (ti > 0.0001f) {
                Ponto p = raio.equacaoRaio(ti);
                float PmenosBdotu = (p.subPonto(B)).produtoEscalar(u);

                if (PmenosBdotu >= 0 && PmenosBdotu <= H) {
                    temIntersecao = true;
                    tEscolhido = min(tEscolhido, ti);
                }
            }
        }
    }

    // aqui vai ser o caso geral (precisa?)
    if (du != 0) {
        Vetor wB2 = raio.origem.subPonto(B);
        Vetor wT2 = raio.origem.subPonto(T);

        float ttopo2 = -(wT2.produtoEscalar(u)/du);
        float tbase2 = -(wB2.produtoEscalar(u)/du);
        
        if (tbase2 > 0.0001f) {
            Ponto p_base = raio.equacaoRaio(tbase2);
            Vetor v_base = p_base.subPonto(B);
            float dist_base = v_base.norma();
            
            if (dist_base <= R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, tbase2);
            }
        }
        
        if (ttopo2 > 0.0001f) {
            Ponto p_topo = raio.equacaoRaio(ttopo2);
            Vetor v_topo = p_topo.subPonto(T);
            float dist_topo = v_topo.norma();
            
            if (dist_topo <= R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, ttopo2);
            }
        }
    }
    
    if (temIntersecao) {
        t = tEscolhido;
        return true;
    }
    
    return false;
}

Cor Cilindro::calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
    Vetor Pi_B = Pi.subPonto(B);                
    float proj = Pi_B.produtoEscalar(u);        
    Vetor P_proj = u.multiEscalar(proj);        
    Vetor n = Pi_B.subVetor(P_proj).normalizado(); 

    Vetor P_F_minus_Pi = fonte.P_F.subPonto(Pi);
    Vetor l = P_F_minus_Pi.normalizado();

    Vetor v = direcao_raio.vetorNegativo();

    float produto_nl = n.produtoEscalar(l);
    Vetor r = n.multiEscalar(2.0f * produto_nl).subVetor(l);

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