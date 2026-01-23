#include "../trabalho_final/include/Cilindro.h"
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

Vetor Cilindro::calcularNormal(Ponto& Pi, Vetor& direcao_raio) {
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
    
    return n;
}

void Cilindro::aplicarTransformacao(const Matriz& transformacao) {
    P = P.aplicarTransformacao(transformacao);
    B = B.aplicarTransformacao(transformacao);

    Matriz normal_transform = Matriz::transposta(Matriz::inversa(transformacao));
    u = u.aplicarTransformacao(normal_transform).normalizado();
}

void Cilindro::transladar(float tx, float ty, float tz) {
    Matriz T = Matriz::translacao(tx, ty, tz);
    
    P = P.aplicarTransformacao(T);
    B = B.aplicarTransformacao(T);
}

Ponto Cilindro::calcularCentro() {
    Vetor uH = u.multiEscalar(H/2.0f);
    return B.somarVetor(uH);
}

Ponto Cilindro::getCentro() {
    return calcularCentro();
}

void Cilindro::escalar(float sx, float sy, float sz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz S = Matriz::escala(sx, sy, sz);
    
    P = P.aplicarTransformacao(S);
    B = B.aplicarTransformacao(S);

    R *= sx;
    H *= sy;

    Matriz N = Matriz::transposta(Matriz::inversa(S));
    u = u.aplicarTransformacao(N).normalizado();
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::rotacionarX(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoX(angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::rotacionarY(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoY(angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::rotacionarZ(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoZ(angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::rotacionarArbitrario(const Vetor& eixo, float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoArbitraria(eixo, angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::cisalharXY(float shx, float shy) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoXY(shx, shy);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::cisalharXZ(float shx, float shz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoXZ(shx, shz);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cilindro::cisalharYZ(float shy, float shz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoYZ(shy, shz);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

// void Cilindro::espelharXY() {
//     Matriz E = Matriz::espelhamentoXY();
//     aplicarTransformacao(E);
// }

// void Cilindro::espelharXZ() {
//     Matriz E = Matriz::espelhamentoXZ();
//     aplicarTransformacao(E);
// }

// void Cilindro::espelharYZ() {
//     Matriz E = Matriz::espelhamentoYZ();
//     aplicarTransformacao(E);
// }