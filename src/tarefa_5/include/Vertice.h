#ifndef VERTICE_H
#define VERTICE_H

#include "Ponto.h"
#include "Vetor.h"

class Vertice {
    public:
        Ponto v;
        Vetor normal;

        Vertice();
        Vertice(Ponto& v, Vetor& normal);
};

#endif