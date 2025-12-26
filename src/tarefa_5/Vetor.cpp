#include "../tarefa_5/include/Vetor.h"
#include "../tarefa_5/include/Matriz.h"
#include <cmath>


Vetor::Vetor() : x(0), y(0), z(0) {}
Vetor::Vetor(float x, float y, float z) : x(x), y(y), z(z) {}
Vetor::Vetor(float v[3]) : x(v[0]), y(v[1]), z(v[2]) {}

Vetor Vetor::somarVetor(Vetor& v) {
    return Vetor(x + v.x, y + v.y, z + v.z);
}

Vetor Vetor::subVetor(Vetor& v) {
    return Vetor(x - v.x, y - v.y, z - v.z);
}

Vetor Vetor::multiEscalar(float t) {
    return Vetor(x * t, y * t, z * t);
}

Vetor Vetor::divEscalar(float t) {
    return Vetor(x/t, y/t, z/t);
}

Vetor Vetor::vetorNegativo() {
    return Vetor(-x, -y, -z);
}

float Vetor::produtoEscalar(Vetor& v) {
    return x * v.x + y * v.y + z * v.z;
}

Vetor Vetor::produtoVetorial(Vetor& v) {
    return Vetor(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

float Vetor::norma() {
    return sqrt(x * x + y * y + z * z);
}

Vetor Vetor::normalizado() {
    float n = norma();
    return Vetor(x/n, y/n, z/n);
}

Vetor Vetor::multiComponente(Vetor& v) {
    return Vetor(x * v.x, y * v.y, z * v.z);
}

Vetor Vetor::aplicarTransformacao(const Matriz& m) {
    return m.multiplicarVetor(*this);
}