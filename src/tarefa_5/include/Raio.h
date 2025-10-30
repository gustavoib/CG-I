#ifndef RAIO_H
#define RAIO_H

#include "Ponto.h"
#include "Vetor.h"

class Raio {
public:
    Ponto origem;
    Vetor direcao;

    Raio(const Ponto& origem, const Vetor& direcao);
    Ponto equacaoRaio(float t);
};

#endif