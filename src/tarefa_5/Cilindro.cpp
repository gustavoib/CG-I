#include "Cilindro.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cfloat>

using namespace std;

Cilindro::Cilindro(Ponto& P, Ponto& B, Vetor& u, float H, float R, bool temBase, bool temTopo, Cor& ke, Cor& kd, Cor& ka, float m)
: ObjetoAbstrato(ke, kd, ka, m), P(P), B(B), u(u), H(H), R(R), temBase(temBase), temTopo(temTopo) {};

bool Cilindro::intersecao(Raio& raio, float& t) {
    Vetor PmenosB = raio.origem.subPonto(B);
    float PBdotu = PmenosB.produtoEscalar(u);
    Vetor PBuu = u.multiEscalar(PBdotu);
    Vetor v = PmenosB.subVetor(PBuu);

    float du = raio.direcao.produtoEscalar(u);
    Vetor duu = u.multiEscalar(du);
    Vetor w = raio.direcao.subVetor(duu);

    float a = w.produtoEscalar(w);
    float b = (v.produtoEscalar(w));
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

        if (temBase && tbase > 0.0001f) {
            Ponto Pibase = raio.equacaoRaio(tbase);
            float distBase = (Pibase.subPonto(B)).norma();
            if (distBase <= R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, tbase);
            }
        }

        if (temTopo && ttopo > 0.0001f) {
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

    float delta = b*b - a*c;

    if (delta >= 0) {
        float t1 = (-b - sqrt(delta))/(a);
        float t2 = (-b + sqrt(delta))/(a);

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
        
        if (temBase && tbase2 > 0.0001f) {
            Ponto p_base = raio.equacaoRaio(tbase2);
            Vetor v_base = p_base.subPonto(B);
            float dist_base = v_base.norma();
            
            if (dist_base <= R) {
                temIntersecao = true;
                tEscolhido = min(tEscolhido, tbase2);
            }
        }
        
        if (temTopo && ttopo2 > 0.0001f) {
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
    
    Vetor n;
    // ponto na base
    if (proj < 0.0001f) {
        n = u.vetorNegativo();
    } 
    // ponto no topo
    else if (proj > H - 0.0001f) {
        n = u;
    } 
    // ponto na lateral
    else {
        Vetor P_proj = u.multiEscalar(proj);        
        n = Pi_B.subVetor(P_proj).normalizado();
    }

    if ((!temBase || !temTopo) && n.produtoEscalar(direcao_raio) > 0) {
        n = n.vetorNegativo();
    }

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

void Cilindro::aplicarTransformacao(const Matriz& transformacao) {
    // Transformar os pontos
    P = P.aplicarTransformacao(transformacao);
    B = B.aplicarTransformacao(transformacao);
    
    // Transformar o vetor direção (usar matriz inversa transposta para vetores normais)
    Matriz normal_transform = Matriz::transposta(Matriz::inversa(transformacao));
    u = u.aplicarTransformacao(normal_transform).normalizado();
}

void Cilindro::transladar(float tx, float ty, float tz) {
    Matriz T = Matriz::translacao(tx, ty, tz);
    
    // Para translação, apenas os pontos mudam
    P = P.aplicarTransformacao(T);
    B = B.aplicarTransformacao(T);
    // u não muda (vetores de direção não são afetados por translação)
}

void Cilindro::escalar(float fator) {
    escalar(fator, fator, fator);
}

void Cilindro::escalar(float sx, float sy, float sz) {
    Matriz S = Matriz::escala(sx, sy, sz);
    
    // Transformar pontos
    P = P.aplicarTransformacao(S);
    B = B.aplicarTransformacao(S);
    
    // Escalar raio e altura proporcionalmente
    // Assumindo que o cilindro está alinhado com o eixo Y
    R *= sx; // ou sy, dependendo da orientação
    H *= sy; // ou sz
    
    // Transformar vetor direção
    Matriz N = Matriz::transposta(Matriz::inversa(S));
    u = u.aplicarTransformacao(N).normalizado();
}

void Cilindro::rotacionarX(float angulo) {
    Matriz R = Matriz::rotacaoX(angulo);
    aplicarTransformacao(R);
}

void Cilindro::rotacionarY(float angulo) {
    Matriz R = Matriz::rotacaoY(angulo);
    aplicarTransformacao(R);
}

void Cilindro::rotacionarZ(float angulo) {
    Matriz R = Matriz::rotacaoZ(angulo);
    aplicarTransformacao(R);
}

void Cilindro::rotacionarEixo(Vetor eixo, float angulo) {
    Matriz R = Matriz::rotacaoArbitraria(eixo, angulo);
    aplicarTransformacao(R);
}

void Cilindro::espelharXY() {
    Matriz E = Matriz::espelhamentoXY();
    aplicarTransformacao(E);
}

void Cilindro::espelharXZ() {
    Matriz E = Matriz::espelhamentoXZ();
    aplicarTransformacao(E);
}

void Cilindro::espelharYZ() {
    Matriz E = Matriz::espelhamentoYZ();
    aplicarTransformacao(E);
}

void Cilindro::cisalharXY(float shx, float shy) {
    Matriz C = Matriz::cisalhamentoXY(shx, shy);
    aplicarTransformacao(C);
}

void Cilindro::cisalharXZ(float shx, float shz) {
    Matriz C = Matriz::cisalhamentoXZ(shx, shz);
    aplicarTransformacao(C);
}

void Cilindro::cisalharYZ(float shy, float shz) {
    Matriz C = Matriz::cisalhamentoYZ(shy, shz);
    aplicarTransformacao(C);
}