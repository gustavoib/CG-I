#ifndef PLANO_H
#define PLANO_H

#include "Objetoabstrato.h"
#include "Ponto.h"
#include "vetor.h"
#include "Textura.h"
#include <vector>
#include <memory>

class Plano : public ObjetoAbstrato {
public:
    Vetor n;
    Ponto P_pi;
    
    std::shared_ptr<Textura> textura;
    bool usarTextura;
    float escalaU;
    float escalaV;

    Plano(Vetor& n, Ponto& p, Cor& ke, Cor& kd, Cor& ka, float m);
    
    Plano(Vetor& n, Ponto& p, std::shared_ptr<Textura> tex,
          float escalaU = 1.0f, float escalaV = 1.0f, float m = 10.0f);

    bool intersecao(Raio& raio, float& t) override;
    Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) override;
    
    void setTextura(std::shared_ptr<Textura> tex, float escU = 1.0f, float escV = 1.0f);
    
private:
    void calcularUV(Ponto& p, float& u, float& v);
    Cor obterCorDifusa(Ponto& pontoIntersecao);
};

#endif