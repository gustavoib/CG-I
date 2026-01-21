#ifndef CONE_H
#define CONE_H

#include "Objetoabstrato.h"
#include "Vetor.h"
#include "Ponto.h"
#include "Matriz.h"

class Cone: public ObjetoAbstrato {
    public:
        Ponto P; // ponto qualquer da superfície do cone
        Ponto Cb; // centro da base do cone
        Vetor n; // vetor unitário que define direção e o sentido do eixo do cone
        float theta; // ângulo que a geratriz forma com o eixo do cone
        float H; // altura
        float R; // raio da base do cone
        bool temBase;

        Cone(Ponto& P, Ponto& Cb, Vetor& n, float theta, float H, float R, bool temBase, Cor& ke, Cor& kd, Cor& ka, float m);
        
        bool intersecao(Raio& raio, float& t) override;
        Vetor calcularNormal(Ponto& Pi, Vetor& direcao_raio) override;

        Ponto calcularCentro();
        void aplicarTransformacao(const Matriz& transformacao);
        void transladar(float tx, float ty, float tz) override;
        void escalar(float fator);
        void escalar(float sx, float sy, float sz) override;
        void rotacionarX(float angulo) override;
        void rotacionarY(float angulo) override;
        void rotacionarZ(float angulo) override;
        void rotacionarEixo(Vetor eixo, float angulo);
        void espelharXY();
        void espelharXZ();
        void espelharYZ();
        void cisalharXY(float shx, float shy) override;
        void cisalharXZ(float shx, float shz) override;
        void cisalharYZ(float shy, float shz) override;
};

#endif