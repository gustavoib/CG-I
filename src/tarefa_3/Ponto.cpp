#include "Ponto.h"

Ponto::Ponto(float x, float y, float z) : x(x), y(y), z(z) {}

Vetor Ponto::subPonto(Ponto& p2) {
    return Vetor(x - p2.x, y - p2.y, z - p2.z);
}