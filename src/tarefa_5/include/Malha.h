#ifndef MALHA_H
#define MALHA_H

#include <vector>
#include "Vertice.h"
#include "Aresta.h"
#include "Face.h"
#include "ObjetoAbstrato.h"

using namespace std;

class Malha : public ObjetoAbstrato {
    public:
        vector<Vertice> vertices;
        vector<Aresta> arestas;
        vector<Face> faces;
        Vetor normalIntersecao;

        Malha();
        Malha(vector<Vertice>& vertices, vector<Aresta>& arestas, vector<Face>& faces, Cor& ke, Cor& kd, Cor& ka, float m);
        void adicionarVertice(Vertice& v);
        void adicionarAresta(Aresta& a);
        void adicionarFace(Face& f);

        bool intersecao(Raio& raio, float& t) override;
        Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;
};

#endif