#ifndef ESFERA_H
#define ESFERA_H

#include "Objetoabstrato.h"
#include "Ponto.h"
#include "Cor.h"
#include <vector>

class Esfera : public ObjetoAbstrato {
    public:
        float raio_esfera;
        Ponto centro_esfera;
        
        Esfera(float raio, Ponto& centro, Cor& ke, Cor& kd, Cor& ka, float m);
        
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