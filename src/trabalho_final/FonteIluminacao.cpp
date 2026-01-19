#include "include/FonteIluminacao.h"
#include "include/Cor.h"
#include "include/Ponto.h"
#include "include/Vetor.h"
#include <algorithm>
#include <cmath>

FonteIluminacao::FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente) 
    : I_F(intensidade), P_F(posicao), I_A(ambiente) {}

Vetor FonteIluminacao::calcularDirecaoLuz(Ponto& ponto) {
    return P_F.subPonto(ponto).normalizado();
}

Vetor FonteIluminacao::calcularVetorReflexao(Vetor& normal, Vetor& direcaoLuz) {
    float produto_nl = normal.produtoEscalar(direcaoLuz);
    return normal.multiEscalar(2.0f * produto_nl).subVetor(direcaoLuz);
}

Cor FonteIluminacao::calcularComponenteAmbiente(Cor& Ka) {
    return I_A.multiComponente(Ka);
}

Cor FonteIluminacao::calcularComponenteDifusa(Vetor& normal, Vetor& direcaoLuz, Cor& Kd) {
    float produto_nl = std::max(0.0f, normal.produtoEscalar(direcaoLuz));
    Cor IFKd = I_F.multiComponente(Kd);
    return IFKd.multiEscalar(produto_nl);
}

Cor FonteIluminacao::calcularComponenteEspecular(Vetor& reflexao, Vetor& observador, Cor& Ke, float m) {
    float produto_vr = std::max(0.0f, observador.produtoEscalar(reflexao));
    float vrm = std::pow(produto_vr, m);
    Cor IFKe = I_F.multiComponente(Ke);
    return IFKe.multiEscalar(vrm);
}

Cor FonteIluminacao::calcularIluminacao(Ponto& pontoIntersecao, 
                                         Vetor& normal, 
                                         Vetor& direcaoObservador,
                                         Cor& Ke, 
                                         Cor& Kd, 
                                         Cor& Ka, 
                                         float m) {
    // calcular direção da luz
    Vetor direcaoLuz = calcularDirecaoLuz(pontoIntersecao);
    
    // calcular vetor de reflexão
    Vetor reflexao = calcularVetorReflexao(normal, direcaoLuz);
    
    // calcular componentes de iluminação
    Cor componenteAmbiente = calcularComponenteAmbiente(Ka);
    Cor componenteDifusa = calcularComponenteDifusa(normal, direcaoLuz, Kd);
    Cor componenteEspecular = calcularComponenteEspecular(reflexao, direcaoObservador, Ke, m);
    
    // combinar componentes
    Cor corFinal = componenteAmbiente.somarCor(componenteDifusa).somarCor(componenteEspecular);
    corFinal.limitar();
    
    return corFinal;
}
