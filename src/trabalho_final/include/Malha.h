#ifndef MALHA_H
#define MALHA_H

#include <vector>
#include "Vertice.h"
#include "Aresta.h"
#include "Face.h"
#include "ObjetoAbstrato.h"

using namespace std;

class Matriz;

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

        void aplicarTransformacao(const Matriz& m_pontos, const Matriz& m_normais);
        Ponto calcularCentro();
        void escalar(float sx, float sy, float sz);
        void transladar(float tx, float ty, float tz);
        void rotacionarX(float angulo);
        void rotacionarY(float angulo);
        void rotacionarZ(float angulo);
        void rotacionarArbitrario(const Vetor& eixo, float angulo);
        void espelharXY();
        void espelharXZ();
        void espelharYZ();
        void cisalharXY(float shx, float shy);
        void cisalharXZ(float shx, float shz);
        void cisalharYZ(float shy, float shz);

        bool intersecao(Raio& raio, float& t) override;
        Vetor calcularNormal(Ponto& Pi, Vetor& direcao_raio) override;
};

#endif