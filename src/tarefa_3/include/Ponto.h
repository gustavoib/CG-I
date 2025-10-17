#ifndef PONTO_H
#define PONTO_H

#include "Vetor.h"

class Ponto {
    public:
        float x, y, z, tipo;

        Ponto();
        Ponto(float x, float y, float z);

        Vetor subPonto(Ponto& p); 
    };

#endif