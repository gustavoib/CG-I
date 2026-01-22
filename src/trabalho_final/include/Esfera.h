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
        void rotacionarEixo(Vetor eixo, float angulo);
        void espelharXY();
        void espelharXZ();
        void espelharYZ();
        void cisalharXY(float shx, float shy) override;
        void cisalharXZ(float shx, float shz) override;
        void cisalharYZ(float shy, float shz) override;
};

#endif