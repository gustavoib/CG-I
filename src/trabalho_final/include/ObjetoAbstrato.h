#ifndef OBJETO_H
#define OBJETO_H

#include "Raio.h"
#include "Cor.h"
#include "Ponto.h"
#include "Vetor.h"
#include "FonteIluminacao.h"

class ObjetoAbstrato {
public:
    Cor Ke;
    Cor Kd;
    Cor Ka;
    float m;
    
    ObjetoAbstrato() {};
    ObjetoAbstrato(Cor& ke, Cor& kd, Cor& ka, float m) : Ke(ke), Kd(kd), Ka(ka), m(m)  {}
    virtual ~ObjetoAbstrato() {}
    
    virtual bool intersecao(Raio& raio, float& t) = 0;
    virtual Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) = 0;
};

#endif