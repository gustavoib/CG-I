#ifndef FACE_H
#define FACE_H

#include "Aresta.h"

class Face {
    public:
        int idAresta1;
        int idAresta2;
        int idAresta3;

        Face(int aresta1, int aresta2, int aresta3);
};

#endif