#ifndef CAMERA_H
#define CAMERA_H

#include "Ponto.h"
#include "Vetor.h"

class Camera {
public:
    Ponto eye; // posição da câmera
    Ponto at;  // ponto de visada
    Vetor up;  // vetor up (orientação)

    // sistema de coordenadas da câmera (base ortonormal)
    Vetor u, v, n;

    // parâmetros de projeção
    float d;
    float xmin, xmax, ymin, ymax;

    Camera(Ponto eye, Ponto at, Vetor up, float d, 
           float xmin, float xmax, float ymin, float ymax);

    // calcular a base ortonormal da câmera
    void calcularSistemaCoordenadasCamera();

    // gerar um raio a partir das coordenadas da janela
    Vetor gerarDirecaoRaio(float x, float y) const;
};

#endif
