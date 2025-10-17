#ifndef FONTE_ILUMINACAO_H
#define FONTE_ILUMINACAO_H

#include "Cor.h"
#include "Ponto.h"

class FonteIluminacao {
public:
    Cor I_F;
    Ponto P_F;
    Cor I_A;

    FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente);
};

#endif