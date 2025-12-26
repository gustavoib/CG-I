#ifndef MATRIZ_H
#define MATRIZ_H

#include "Vetor.h"
#include "Ponto.h"

class Matriz {
public:
    float m[4][4];

    Matriz();
    Matriz(float valores[4][4]);

    static Matriz identidade();
    static Matriz inversa(const Matriz& matriz);
    static Matriz transposta(const Matriz& matriz);
    static Matriz escala(float sx, float sy, float sz);
    static Matriz translacao(float tx, float ty, float tz);
    static Matriz rotacaoX(float angulo);
    static Matriz rotacaoY(float angulo);
    static Matriz rotacaoZ(float angulo);
    static Matriz rotacaoArbitraria(Vetor eixo, float angulo);
    static Matriz espelhamentoXY();
    static Matriz espelhamentoXZ();
    static Matriz espelhamentoYZ();
    static Matriz cisalhamentoXY(float shx, float shy);
    static Matriz cisalhamentoXZ(float shx, float shz);
    static Matriz cisalhamentoYZ(float shy, float shz);

    Matriz multiplicar(const Matriz& outra) const;
    Vetor multiplicarVetor(const Vetor& v) const;
    Ponto multiplicarPonto(const Ponto& p) const;
};

#endif