#ifndef FONTE_ILUMINACAO_H
#define FONTE_ILUMINACAO_H

#include "Cor.h"
#include "Ponto.h"
#include "Vetor.h"

class FonteIluminacao {
public:
    Cor I_F;    // Intensidade da fonte de luz
    Ponto P_F;  // Posição da fonte de luz
    Cor I_A;    // Intensidade da luz ambiente

    FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente);
    
    // Métodos para cálculos de iluminação
    Cor calcularIluminacao(Ponto& pontoIntersecao, 
                           Vetor& normal, 
                           Vetor& direcaoObservador,
                           Cor& Ke, 
                           Cor& Kd, 
                           Cor& Ka, 
                           float m);
    
    // Métodos auxiliares
    Vetor calcularDirecaoLuz(Ponto& ponto);
    Vetor calcularVetorReflexao(Vetor& normal, Vetor& direcaoLuz);
    
    // Cálculo de componentes individuais
    Cor calcularComponenteAmbiente(Cor& Ka);
    Cor calcularComponenteDifusa(Vetor& normal, Vetor& direcaoLuz, Cor& Kd);
    Cor calcularComponenteEspecular(Vetor& reflexao, Vetor& observador, Cor& Ke, float m);
};

#endif