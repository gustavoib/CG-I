#ifndef CILINDRO_H
#define CILINDRO_H

#include "Objetoabstrato.h"
#include "Vetor.h"
#include "Ponto.h"

class Cilindro: public ObjetoAbstrato {
    public:
        Ponto P; // ponto qualquer na superficie no cilindro
        Ponto B; // centro da base do cilindro
        Vetor u; // vetor unitário que define direção e o sentido do eixo do cilindro
        float H; // altura
        float R; // raio

        Cilindro(Ponto& P, Ponto& B, Vetor& u, float H, float R, Cor& ke, Cor& kd, Cor& ka, float m);
        
        bool intersecao(Raio& raio, float& t) override;
        Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;

};

#endif