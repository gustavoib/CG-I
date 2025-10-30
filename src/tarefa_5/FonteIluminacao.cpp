#include "FonteIluminacao.h"
#include "Cor.h"
#include "Ponto.h"

FonteIluminacao::FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente) : I_F(intensidade), P_F(posicao), I_A(ambiente) {}
