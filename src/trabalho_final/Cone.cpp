#include "../trabalho_final/include/Cone.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cfloat>

using namespace std;

Cone::Cone(Ponto& P, Ponto& Cb, Vetor& n, float theta, float H, float R, bool temBase, Cor& ke, Cor& kd, Cor& ka, float m)
:ObjetoAbstrato(ke, kd, ka, m), P(P), Cb(Cb), n(n), theta(theta), H(H), R(R), temBase(temBase) {};

bool Cone::intersecao(Raio& raio, float& t) {
    Ponto V = Cb.somarVetor(n.multiEscalar(H)); // vértice do cone
    Vetor VmenosP = V.subPonto(raio.origem);

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

    if (temBase && dn != 0) {
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

Vetor Cone::calcularNormal(Ponto& Pi, Vetor& direcao_raio) {
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

            if (!temBase && normal.produtoEscalar(direcao_raio) > 0) {
                normal = normal.vetorNegativo();
            }
        }
    }
    
    return normal;
}

void Cone::aplicarTransformacao(const Matriz& transformacao) {
    P = P.aplicarTransformacao(transformacao);
    Cb = Cb.aplicarTransformacao(transformacao);
    
    // transformar o vetor direção (usar matriz inversa transposta)
    Matriz normal_transform = Matriz::transposta(Matriz::inversa(transformacao));
    n = n.aplicarTransformacao(normal_transform).normalizado();
}

Ponto Cone::calcularCentro() {
    Vetor nH = n.multiEscalar(H/2.0f);
    return Cb.somarVetor(nH);
}

Ponto Cone::getCentro() {
    return calcularCentro();
}

void Cone::transladar(float tx, float ty, float tz) {
    Matriz T = Matriz::translacao(tx, ty, tz);
    P = P.aplicarTransformacao(T);
    Cb = Cb.aplicarTransformacao(T);
}

void Cone::escalar(float sx, float sy, float sz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz S = Matriz::escala(sx, sy, sz);
    
    P = P.aplicarTransformacao(S);
    Cb = Cb.aplicarTransformacao(S);
    
    float escala_raio = (sx + sz)/2.0f;
    R *= escala_raio;
    H *= sy;
    
    theta = atan(R/H);
    
    Matriz N = Matriz::transposta(Matriz::inversa(S));
    n = n.aplicarTransformacao(N).normalizado();
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::rotacionarX(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoX(angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::rotacionarY(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoY(angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::rotacionarZ(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoZ(angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::rotacionarArbitrario(const Vetor& eixo, float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz R = Matriz::rotacaoArbitraria(eixo, angulo);
    aplicarTransformacao(R);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::cisalharXY(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoXY(angulo);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::cisalharYX(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoYX(angulo);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::cisalharXZ(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoXZ(angulo);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::cisalharZX(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoZX(angulo);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::cisalharYZ(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoYZ(angulo);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

void Cone::cisalharZY(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz C = Matriz::cisalhamentoZY(angulo);
    aplicarTransformacao(C);
    
    transladar(centro.x, centro.y, centro.z);
}

// void Cone::espelharXY() {
//     Matriz E = Matriz::espelhamentoXY();
//     aplicarTransformacao(E);
// }

// void Cone::espelharXZ() {
//     Matriz E = Matriz::espelhamentoXZ();
//     aplicarTransformacao(E);
// }

// void Cone::espelharYZ() {
//     Matriz E = Matriz::espelhamentoYZ();
//     aplicarTransformacao(E);
// }