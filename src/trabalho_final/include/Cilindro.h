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
        Vetor calcularNormal(Ponto& Pi, Vetor& direcao_raio) override;

        Ponto calcularCentro();
        Ponto getCentro() override;
        void aplicarTransformacao(const Matriz& transformacao);
        void transladar(float tx, float ty, float tz) override;
        void escalar(float fator);
        void escalar(float sx, float sy, float sz) override;
        void rotacionarX(float angulo) override;
        void rotacionarY(float angulo) override;
        void rotacionarZ(float angulo) override;
        void rotacionarArbitrario(const Vetor& eixo, float angulo) override;
        void espelharXY();
        void espelharXZ();
        void espelharYZ();
        void cisalharXY(float shx, float shy) override;
        void cisalharXZ(float shx, float shz) override;
        void cisalharYZ(float shy, float shz) override;
};

#endif