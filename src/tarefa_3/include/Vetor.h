#ifndef VETOR_H
#define VETOR_H

class Vetor {
    public:
        float x, y, z;

        Vetor();
        Vetor(float x, float y, float z);
        Vetor(float v[3]);

        Vetor somarVetor(Vetor& v);
        Vetor subVetor(Vetor& v);
        Vetor multiEscalar(float t);
        Vetor divEscalar(float t);
        Vetor vetorNegativo();

        float produtoEscalar(Vetor& v);
        float norma();
        Vetor normalizado();
        Vetor multiComponente(Vetor& v);
};

#endif