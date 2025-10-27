#ifndef CONE_H
#define CONE_H

#include "Objetoabstrato.h"
#include "Vetor.h"
#include "Ponto.h"

class Cone: public ObjetoAbstrato {
    public:
        Ponto P; // ponto qualquer da superfície do cone
        Ponto Cb; // centro da base do cone
        Vetor n; // vetor unitário que define direção e o sentido do eixo do cone
        float theta; // ângulo que a geratriz forma com o eixo do cone
        float H; // altura
        float R; // raio da base do cone

        Cone(Ponto& P, Ponto& Cb, Vetor& n, float theta, float H, float R, Cor& ke, Cor& kd, Cor& ka, float m);
        
        bool intersecao(Raio& raio, float& t) override;
        Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;

};

#endif