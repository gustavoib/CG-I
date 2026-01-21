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

    // transformar um ponto do mundo para espaço de câmera
    Vetor worldToCamera(Ponto ponto) const;

    // setter e getter para eye
    void setEye(const Ponto& newEye) { eye = newEye; }
    Ponto getEye() const { return eye; }

    // setter e getter para at
    void setAt(const Ponto& newAt) { at = newAt; }
    Ponto getAt() const { return at; }

    // setter e getter para up
    void setUp(const Vetor& newUp) { up = newUp; }
    Vetor getUp() const { return up; }

    // setter e getter para parâmetros de projeção
    void setD(float newD) { d = newD; }
    float getD() const { return d; }

    void setXmin(float newXmin) { xmin = newXmin; }
    float getXmin() const { return xmin; }

    void setXmax(float newXmax) { xmax = newXmax; }
    float getXmax() const { return xmax; }

    void setYmin(float newYmin) { ymin = newYmin; }
    float getYmin() const { return ymin; }

    void setYmax(float newYmax) { ymax = newYmax; }
    float getYmax() const { return ymax; }
    
};

#endif
