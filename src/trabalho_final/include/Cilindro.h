#ifndef CILINDRO_H
#define CILINDRO_H

#include "Objetoabstrato.h"
#include "Vetor.h"
#include "Ponto.h"
#include "Matriz.h"

class Cilindro: public ObjetoAbstrato {
    public:
        Ponto P; // ponto qualquer na superficie no cilindro
        Ponto B; // centro da base do cilindro
        Vetor u; // vetor unitário que define direção e o sentido do eixo do cilindro
        float H; // altura
        float R; // raio
        bool temBase;
        bool temTopo;

        Cilindro(Ponto& P, Ponto& B, Vetor& u, float H, float R, bool temBase, bool temTopo, Cor& ke, Cor& kd, Cor& ka, float m);
        
        bool intersecao(Raio& raio, float& t) override;
        Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;

        Ponto calcularCentro();
        void aplicarTransformacao(const Matriz& transformacao);
        void transladar(float tx, float ty, float tz);
        void escalar(float fator);
        void escalar(float sx, float sy, float sz);
        void rotacionarX(float angulo);
        void rotacionarY(float angulo);
        void rotacionarZ(float angulo);
        void rotacionarEixo(Vetor eixo, float angulo);
        void espelharXY();
        void espelharXZ();
        void espelharYZ();
        void cisalharXY(float shx, float shy);
        void cisalharXZ(float shx, float shz);
        void cisalharYZ(float shy, float shz);
};

#endif