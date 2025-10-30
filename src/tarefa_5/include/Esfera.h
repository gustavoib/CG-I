#ifndef ESFERA_H
#define ESFERA_H

#include "Objetoabstrato.h"
#include "Ponto.h"
#include "Cor.h"
#include <vector>

class Esfera : public ObjetoAbstrato {
    public:
        float raio_esfera;
        Ponto centro_esfera;
        
        Esfera(float raio, Ponto& centro, Cor& ke, Cor& kd, Cor& ka, float m);
        
        bool intersecao(Raio& raio, float& t) override;
        Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;
};

#endif