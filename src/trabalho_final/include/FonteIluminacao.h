#ifndef FONTE_ILUMINACAO_H
#define FONTE_ILUMINACAO_H

#include "Cor.h"
#include "Ponto.h"
#include "Vetor.h"

class FonteIluminacao {
public:
    Cor I_F;
    Ponto P_F;
    Cor I_A;

    // Parâmetros da spot light
    Vetor df;          // Direção da spot light (normalizado)
    float theta;       // Ângulo de abertura da zona de iluminação (em radianos)
    bool ehSpotLight;  // Flag para usar spot light

    FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente);
    
    FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente, Vetor& direcao, float theta_graus, bool ativo = true);

    // métodos para cálculos de iluminação
    Cor calcularIluminacao(Ponto& pontoIntersecao, Vetor& normal, Vetor& direcaoObservador, Cor& Ke, Cor& Kd, Cor& Ka, float m);
    
    // métodos auxiliares
    Vetor calcularDirecaoLuz(Ponto& ponto);
    Vetor calcularVetorReflexao(Vetor& normal, Vetor& direcaoLuz);
    
    // cálculo de componentes individuais
    Cor calcularComponenteAmbiente(Cor& Ka);
    Cor calcularComponenteDifusa(Vetor& normal, Vetor& direcaoLuz, Cor& Kd);
    Cor calcularComponenteEspecular(Vetor& reflexao, Vetor& observador, Cor& Ke, float m);

    bool estaNoAreaIluminacao(Ponto& pontoIntersecao);
    float calcularIntensidadeSpot(Ponto& pontoIntersecao);
    
    // getters e setters para posição da fonte
    void setPosicao(const Ponto& novaPosicao) { P_F = novaPosicao; }
    Ponto getPosicao() const { return P_F; }
};

#endif