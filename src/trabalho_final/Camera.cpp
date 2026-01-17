#include "include/Camera.h"

Camera::Camera(Ponto eye, Ponto at, Vetor up, float d, float xmin, float xmax, float ymin, float ymax)
    : eye(eye), at(at), up(up), d(d), xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {
    calcularSistemaCoordenadasCamera();
}

void Camera::calcularSistemaCoordenadasCamera() {
    // calcular o vetor n (direção oposta à visada)
    n = eye.subPonto(at).normalizado();
    
    // Calcular o vetor u (direção direita da câmera)
    u = up.produtoVetorial(n).normalizado();
    
    // Calcular o vetor v (direção para cima da câmera)
    v = n.produtoVetorial(u).normalizado();
}

Vetor Camera::gerarDirecaoRaio(float x, float y) const {
    Vetor u_temp = u;
    Vetor v_temp = v;
    Vetor n_temp = n;
    
    Vetor direcao = u_temp.multiEscalar(x);
    Vetor v_component = v_temp.multiEscalar(y);
    Vetor n_component = n_temp.multiEscalar(-d);
    
    direcao = direcao.somarVetor(v_component);
    direcao = direcao.somarVetor(n_component);
    
    return direcao.normalizado();
}

Vetor Camera::worldToCamera(Ponto ponto) const {
    // translação do ponto do mundo em relação ao olho
    Vetor p = ponto.subPonto(const_cast<Ponto&>(eye));
    
    // projeção (Rotação) - usando produto escalar para obter coordenadas na base da câmera
    float x = p.produtoEscalar(const_cast<Vetor&>(u));
    float y = p.produtoEscalar(const_cast<Vetor&>(v));
    float z = p.produtoEscalar(const_cast<Vetor&>(n));
    
    return Vetor(x, y, z);
}
