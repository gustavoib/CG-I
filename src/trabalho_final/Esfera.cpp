#include "../trabalho_final/include/Esfera.h"
#include "Matriz.h"
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

Vetor Esfera::calcularNormal(Ponto& Pi, Vetor& /*direcao_raio*/) {
    return Pi.subPonto(centro_esfera).normalizado();
}

Ponto Esfera::calcularCentro() {
    return centro_esfera;
}

Ponto Esfera::getCentro() {
    return centro_esfera;
}

void Esfera::transladar(float tx, float ty, float tz) {
    Matriz trans = Matriz::translacao(tx, ty, tz);
    centro_esfera = trans.multiplicarPonto(centro_esfera);
}

void Esfera::escalar(float sx, float sy, float sz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    float maior_escala = max({sx, sy, sz});
    raio_esfera *= maior_escala;
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::rotacionarX(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz rot = Matriz::rotacaoX(angulo);
    centro_esfera = rot.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::rotacionarY(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz rot = Matriz::rotacaoY(angulo);
    centro_esfera = rot.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::rotacionarZ(float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz rot = Matriz::rotacaoZ(angulo);
    centro_esfera = rot.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::rotacionarEixo(Vetor eixo, float angulo) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz rot = Matriz::rotacaoArbitraria(eixo, angulo);
    centro_esfera = rot.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::cisalharXY(float shx, float shy) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz cis = Matriz::cisalhamentoXY(shx, shy);
    centro_esfera = cis.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::cisalharXZ(float shx, float shz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz cis = Matriz::cisalhamentoXZ(shx, shz);
    centro_esfera = cis.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

void Esfera::cisalharYZ(float shy, float shz) {
    Ponto centro = calcularCentro();
    transladar(-centro.x, -centro.y, -centro.z);
    
    Matriz cis = Matriz::cisalhamentoYZ(shy, shz);
    centro_esfera = cis.multiplicarPonto(centro_esfera);
    
    transladar(centro.x, centro.y, centro.z);
}

// void Esfera::espelharXY() {
//     Matriz esp = Matriz::espelhamentoXY();
//     centro_esfera = esp.multiplicarPonto(centro_esfera);
// }

// void Esfera::espelharXZ() {
//     Matriz esp = Matriz::espelhamentoXZ();
//     centro_esfera = esp.multiplicarPonto(centro_esfera);
// }

// void Esfera::espelharYZ() {
//     Matriz esp = Matriz::espelhamentoYZ();
//     centro_esfera = esp.multiplicarPonto(centro_esfera);
// }