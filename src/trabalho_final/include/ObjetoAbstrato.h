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
    
    virtual Vetor calcularNormal(Ponto& Pi, Vetor& direcao_raio) = 0;
    
    virtual Cor obterCorDifusa(Ponto& /*Pi*/) {
        return Kd;
    }
    
    virtual Cor calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
        Vetor normal = calcularNormal(Pi, direcao_raio);
        Vetor observador = direcao_raio.vetorNegativo();
        Cor corDifusa = obterCorDifusa(Pi);
        
        return fonte.calcularIluminacao(Pi, normal, observador, Ke, corDifusa, Ka, m);
    }
    
    // métodos virtuais de transformação (implementação padrão vazia)
    virtual void transladar(float /*tx*/, float /*ty*/, float /*tz*/) {}
    virtual void escalar(float /*sx*/, float /*sy*/, float /*sz*/) {}
    virtual void rotacionarX(float /*angulo*/) {}
    virtual void rotacionarY(float /*angulo*/) {}
    virtual void rotacionarZ(float /*angulo*/) {}
    virtual void rotacionarArbitrario(const Vetor& /*eixo*/, float /*angulo*/) {}
    virtual void cisalharXY(float /*angulo*/) {}
    virtual void cisalharYX(float /*angulo*/) {}
    virtual void cisalharXZ(float /*angulo*/) {}
    virtual void cisalharZX(float /*angulo*/) {}
    virtual void cisalharYZ(float /*angulo*/) {}
    virtual void cisalharZY(float /*angulo*/) {}

    // método para obter o centro do objeto
    virtual Ponto getCentro() {
        return Ponto(0.0f, 0.0f, 0.0f);
    }
};

#endif