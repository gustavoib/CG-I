#ifndef CUBO_H
#define CUBO_H

#include "Malha.h"
#include "Ponto.h"

class Cubo : public Malha {
    public:
        Malha criarCubo(Ponto& centro, float lado, Cor& ke, Cor& kd, Cor& ka, float m);
};

#endif