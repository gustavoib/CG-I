#include "include/FonteIluminacao.h"
#include "include/Cor.h"
#include "include/Ponto.h"
#include "include/Vetor.h"
#include <algorithm>
#include <cmath>

FonteIluminacao::FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente) 
    : I_F(intensidade), P_F(posicao), I_A(ambiente) {}

FonteIluminacao::FonteIluminacao(const Cor& intensidade, const Ponto& posicao, const Cor& ambiente, Vetor& direcao, float theta_graus, bool ativo)
    : I_F(intensidade), P_F(posicao), I_A(ambiente), ehSpotLight(ativo) {
    // Converter theta de graus para radianos
    theta = theta_graus * 3.14159265358979323846f / 180.0f;
    // Normalizar a direção
    df = direcao.normalizado();
}

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

bool FonteIluminacao::estaNoAreaIluminacao(Ponto& pontoIntersecao) {
    if (!ehSpotLight) {
        return true;  // Luz pontual normal, tudo está iluminado
    }
    
    // Calcular vetor l: de Pi até Pf
    Vetor l = P_F.subPonto(pontoIntersecao).normalizado();
    
    // Calcular cos(alfa) = -l . df
    float cosAlfa = -(l.produtoEscalar(df));
    
    // Calcular cos(theta)
    float cosTheta = std::cos(theta);
    
    // Se cos(alfa) >= cos(theta), então alfa <= theta, está na área de iluminação
    return cosAlfa >= cosTheta;
}

float FonteIluminacao::calcularIntensidadeSpot(Ponto& pontoIntersecao) {
    if (!ehSpotLight) {
        return 1.0f;  // Intensidade máxima para luz normal
    }
    
    // Calcular vetor l: de Pi até Pf
    Vetor l = P_F.subPonto(pontoIntersecao).normalizado();
    
    // Calcular cos(alfa) = -l . df
    float cosAlfa = -(l.produtoEscalar(df));
    
    // Calcular cos(theta)
    float cosTheta = std::cos(theta);
    
    // Se não está na área de iluminação, retornar 0
    if (cosAlfa < cosTheta) {
        return 0.0f;
    }
    
    // Intensidade = cos(alfa)
    return std::max(0.0f, cosAlfa);
}

Cor FonteIluminacao::calcularIluminacao(Ponto& pontoIntersecao, Vetor& normal, Vetor& direcaoObservador,Cor& Ke, Cor& Kd, Cor& Ka, float m) {
    // Se é uma spot light, verificar se o ponto está na área de iluminação
    if (ehSpotLight && !estaNoAreaIluminacao(pontoIntersecao)) {
        // Retornar apenas iluminação ambiente
        return calcularComponenteAmbiente(Ka);
    }
    
    // calcular direção da luz
    Vetor direcaoLuz = calcularDirecaoLuz(pontoIntersecao);
    
    // calcular vetor de reflexão
    Vetor reflexao = calcularVetorReflexao(normal, direcaoLuz);
    
    // calcular componentes de iluminação
    Cor componenteAmbiente = calcularComponenteAmbiente(Ka);
    Cor componenteDifusa = calcularComponenteDifusa(normal, direcaoLuz, Kd);
    Cor componenteEspecular = calcularComponenteEspecular(reflexao, direcaoObservador, Ke, m);
    
    // Para spot light, modular a intensidade de difusa e especular
    float intensidadeSpot = calcularIntensidadeSpot(pontoIntersecao);
    componenteDifusa = componenteDifusa.multiEscalar(intensidadeSpot);
    componenteEspecular = componenteEspecular.multiEscalar(intensidadeSpot);
    
    // combinar componentes
    Cor corFinal = componenteAmbiente.somarCor(componenteDifusa).somarCor(componenteEspecular);
    corFinal.limitar();
    
    return corFinal;
}
