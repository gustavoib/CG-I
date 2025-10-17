#ifndef PLANO_H
#define PLANO_H

#include "Objetoabstrato.h"
#include "Ponto.h"
#include "vetor.h"
#include <vector>

class Plano : public ObjetoAbstrato {
    public:
        Vetor n;
        Ponto P_pi;

        Plano(Vetor& n, Ponto& p, Cor& ke, Cor& kd, Cor& ka, float m);

        bool intersecao(Raio& raio, float& t) override;
        Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;
};

#endif