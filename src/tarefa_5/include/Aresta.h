#ifndef ARESTA_H
#define ARESTA_H

#include "Vertice.h"
#include "Vetor.h"

class Aresta {
    public:
        int idVertice1;
        int idVertice2;

        Aresta(int idVertice1, int idVertice2);
};

#endif