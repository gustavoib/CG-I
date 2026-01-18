#include "../trabalho_final/include/Ponto.h"
#include "../trabalho_final/include/Matriz.h"

Ponto::Ponto() : x(0.0f), y(0.0f), z(0.0f) {}

Ponto::Ponto(float x, float y, float z) : x(x), y(y), z(z) {}

Vetor Ponto::subPonto(Ponto& p2) {
    return Vetor(x - p2.x, y - p2.y, z - p2.z);
}

Ponto Ponto::somarVetor(const Vetor& v) {
    return Ponto(x + v.x, y + v.y, z + v.z);
}

Ponto Ponto::aplicarTransformacao(const Matriz& m) {
    return m.multiplicarPonto(*this);
}