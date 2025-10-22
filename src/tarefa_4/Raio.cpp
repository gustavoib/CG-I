#include "Raio.h"
#include "Ponto.h"
#include <cmath>

Raio::Raio(const Ponto& origem, const Vetor& direcao) : origem(origem), direcao(direcao) {}

Ponto Raio::equacaoRaio(float t) {
    float x = origem.x + t * direcao.x;
    float y = origem.y + t * direcao.y;
    float z = origem.z + t * direcao.z;
    return Ponto(x, y, z);
}
