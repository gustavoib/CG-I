#include "../include/Malha.h"
#include "../include/Cubo.h"
#include "../include/Vertice.h"

Malha Cubo::criarCubo(Ponto& centro, float lado, Cor& ke, Cor& kd, Cor& ka, float m) {
    // setando cubo
    Malha cubo;
    cubo.Ke = ke;
    cubo.Kd = kd;
    cubo.Ka = ka;
    cubo.m = m;

    // adicionando os oito vertices
    Ponto p1(centro.x - lado/2, centro.y, centro.z - lado/2);
    Vetor n1(0, 0, 0);
    Vertice v1(p1, n1);
    cubo.adicionarVertice(v1);

    Ponto p2(centro.x - lado/2, centro.y, centro.z + lado/2);
    Vetor n2(0, 0, 0);
    Vertice v2(p2, n2);
    cubo.adicionarVertice(v2);

    Ponto p3(centro.x + lado/2, centro.y, centro.z + lado/2);
    Vetor n3(0, 0, 0);
    Vertice v3(p3, n3);
    cubo.adicionarVertice(v3);

    Ponto p4(centro.x + lado/2, centro.y, centro.z - lado/2);
    Vetor n4(0, 0, 0);
    Vertice v4(p4, n4);
    cubo.adicionarVertice(v4);

    Ponto p5(centro.x - lado/2, centro.y + lado, centro.z - lado/2);
    Vetor n5(0, 0, 0);
    Vertice v5(p5, n5);
    cubo.adicionarVertice(v5);

    Ponto p6(centro.x - lado/2, centro.y + lado, centro.z + lado/2);
    Vetor n6(0, 0, 0);
    Vertice v6(p6, n6);
    cubo.adicionarVertice(v6);

    Ponto p7(centro.x + lado/2, centro.y + lado, centro.z + lado/2);
    Vetor n7(0, 0, 0);
    Vertice v7(p7, n7);
    cubo.adicionarVertice(v7);

    Ponto p8(centro.x + lado/2, centro.y + lado, centro.z - lado/2);
    Vetor n8(0, 0, 0);
    Vertice v8(p8, n8);
    cubo.adicionarVertice(v8);

    // adicionando as 18 arestas
    int idA11 = 0;
    int idA12 = 1;
    Aresta aresta1(idA11, idA12);
    cubo.adicionarAresta(aresta1);

    int idA21 = 1;
    int idA22 = 2;
    Aresta aresta2(idA21, idA22);
    cubo.adicionarAresta(aresta2);

    int idA31 = 2;
    int idA32 = 3;
    Aresta aresta3(idA31, idA32);
    cubo.adicionarAresta(aresta3);

    int idA41 = 3;
    int idA42 = 0;
    Aresta aresta4(idA41, idA42);
    cubo.adicionarAresta(aresta4);

    int idA51 = 4;
    int idA52 = 5;
    Aresta aresta5(idA51, idA52);
    cubo.adicionarAresta(aresta5);

    int idA61 = 5;
    int idA62 = 6;
    Aresta aresta6(idA61, idA62);
    cubo.adicionarAresta(aresta6);

    int idA71 = 6;
    int idA72 = 7;
    Aresta aresta7(idA71, idA72);
    cubo.adicionarAresta(aresta7);

    int idA81 = 7;
    int idA82 = 4;
    Aresta aresta8(idA81, idA82);
    cubo.adicionarAresta(aresta8);

    int idA91 = 0;
    int idA92 = 4;
    Aresta aresta9(idA91, idA92);
    cubo.adicionarAresta(aresta9);

    int idA101 = 1;
    int idA102 = 5;
    Aresta aresta10(idA101, idA102);
    cubo.adicionarAresta(aresta10);

    int idA111 = 2;
    int idA112 = 6;
    Aresta aresta11(idA111, idA112);
    cubo.adicionarAresta(aresta11);

    int idA121 = 3;
    int idA122 = 7;
    Aresta aresta12(idA121, idA122);
    cubo.adicionarAresta(aresta12);

    int idA131 = 2;
    int idA132 = 7;
    Aresta aresta13(idA131, idA132);
    cubo.adicionarAresta(aresta13);

    int idA141 = 5;
    int idA142 = 7;
    Aresta aresta14(idA141, idA142);
    cubo.adicionarAresta(aresta14);

    int idA151 = 5;
    int idA152 = 2;
    Aresta aresta15(idA151, idA152);
    cubo.adicionarAresta(aresta15);

    int idA161 = 1;
    int idA162 = 4;
    Aresta aresta16(idA161, idA162);
    cubo.adicionarAresta(aresta16);

    int idA171 = 1;
    int idA172 = 3;
    Aresta aresta17(idA171, idA172);
    cubo.adicionarAresta(aresta17);

    int idA181 = 3;
    int idA182 = 4;
    Aresta aresta18(idA181, idA182);
    cubo.adicionarAresta(aresta18);

    // adicionando as 12 faces
    int idF11 = 6;
    int idF12 = 10;
    int idF13 = 12;
    Face face1(idF11, idF12, idF13);
    cubo.adicionarFace(face1);

    int idF21 = 12;
    int idF22 = 2;
    int idF23 = 11;
    Face face2(idF21, idF22, idF23);
    cubo.adicionarFace(face2);

    int idF31 = 7;
    int idF32 = 4;
    int idF33 = 13;
    Face face3(idF31, idF32, idF33);
    cubo.adicionarFace(face3);

    int idF41 = 13;
    int idF42 = 5;
    int idF43 = 6;
    Face face4(idF41, idF42, idF43);
    cubo.adicionarFace(face4);

    int idF51 = 5;
    int idF52 = 14;
    int idF53 = 10;
    Face face5(idF51, idF52, idF53);
    cubo.adicionarFace(face5);

    int idF61 = 9;
    int idF62 = 1;
    int idF63 = 14;
    Face face6(idF61, idF62, idF63);
    cubo.adicionarFace(face6);

    int idF71 = 4;
    int idF72 = 15;
    int idF73 = 9;
    Face face7(idF71, idF72, idF73);
    cubo.adicionarFace(face7);

    int idF81 = 8;
    int idF82 = 0;
    int idF83 = 15;
    Face face8(idF81, idF82, idF83);
    cubo.adicionarFace(face8);

    int idF91 = 1;
    int idF92 = 16;
    int idF93 = 2;
    Face face9(idF91, idF92, idF93);
    cubo.adicionarFace(face9);

    int idF101 = 3;
    int idF102 = 16;
    int idF103 = 10;
    Face face10(idF101, idF102, idF103);
    cubo.adicionarFace(face10);

    int idF111 = 11;
    int idF112 = 17;
    int idF113 = 7;
    Face face11(idF111, idF112, idF113);
    cubo.adicionarFace(face11);

    int idF121 = 3;
    int idF122 = 8;
    int idF123 = 17;
    Face face12(idF121, idF122, idF123);
    cubo.adicionarFace(face12);

    return cubo;
}