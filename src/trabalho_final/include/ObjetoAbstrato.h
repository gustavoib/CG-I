#ifndef OBJETO_H
#define OBJETO_H

#include "Raio.h"
#include "Cor.h"
#include "Ponto.h"
#include "Vetor.h"
#include "FonteIluminacao.h"
#include <algorithm>
#include <cmath>

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
    
    // Método virtual para calcular a normal no ponto de interseção
    virtual Vetor calcularNormal(Ponto& Pi, Vetor& direcao_raio) = 0;
    
    // Método virtual para obter a cor difusa (permite textura)
    virtual Cor obterCorDifusa(Ponto& /*Pi*/) {
        return Kd;
    }
    
    // Método geral de iluminação (não precisa ser sobrescrito)
    virtual Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
        Vetor normal = calcularNormal(Pi, direcao_raio);
        Vetor observador = direcao_raio.vetorNegativo();
        Cor corDifusa = obterCorDifusa(Pi);
        
        // Delegar o cálculo para a classe FonteIluminacao
        return fonte.calcularIluminacao(Pi, normal, observador, Ke, corDifusa, Ka, m);
    }
};

#endif