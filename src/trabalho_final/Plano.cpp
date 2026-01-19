#include "../trabalho_final/include/Plano.h"
#include "../trabalho_final/include/Textura.h"
#include <cmath>
#include <algorithm>
#include <memory>

using namespace std;

// Cores padrão estáticas para o construtor com textura
static Cor cor_padrao_ke(1, 1, 1);
static Cor cor_padrao_kd(1, 1, 1);
static Cor cor_padrao_ka(1, 1, 1);

Plano::Plano(Vetor& n, Ponto& p, Cor& ke, Cor& kd, Cor& ka, float m) 
    : ObjetoAbstrato(ke, kd, ka, m), 
      n(n.normalizado()), 
      P_pi(p),
      usarTextura(false),
      escalaU(1.0f),
      escalaV(1.0f) {
}

Plano::Plano(Vetor& n, Ponto& p, std::shared_ptr<Textura> tex, float escU, float escV, float m)
    : ObjetoAbstrato(cor_padrao_ke, cor_padrao_kd, cor_padrao_ka, m), 
      n(n.normalizado()), P_pi(p) {
    textura = tex;
    usarTextura = true;
    escalaU = escU;
    escalaV = escV;
}

bool Plano::intersecao(Raio& raio, float& t) {
    float denominador = n.produtoEscalar(raio.direcao);
    
    if (fabs(denominador) == 0) {
        return false;
    }
    
    Vetor w = raio.origem.subPonto(P_pi);
    t = -w.produtoEscalar(n) / denominador;

    if (t > 0) {
        return true;
    } else {
        return false;
    }
}

void Plano::calcularUV(Ponto& p, float& u, float& v) {
    // Encontra dois vetores perpendiculares ao normal para formar base 2D
    Vetor up(0, 1, 0);
    if (fabs(n.produtoEscalar(up)) > 0.9f) {
        up = Vetor(1, 0, 0);
    }
    
    Vetor tangente = n.produtoVetorial(up).normalizado();
    Vetor bitangente = n.produtoVetorial(tangente).normalizado();
    
    // Projeta o ponto nos vetores tangente e bitangente
    Vetor deslocamento = p.subPonto(P_pi);
    u = deslocamento.produtoEscalar(tangente) * escalaU * 0.01f;
    v = deslocamento.produtoEscalar(bitangente) * escalaV * 0.01f;
}

Cor Plano::obterCorDifusa(Ponto& pontoIntersecao) {
    if (usarTextura && textura) {
        float u, v;
        calcularUV(pontoIntersecao, u, v);
        return textura->obterCor(u, v);
    }
    return Kd;
}

Vetor Plano::calcularNormal(Ponto& /*Pi*/, Vetor& /*direcao_raio*/) {
    return n;
}

void Plano::setTextura(std::shared_ptr<Textura> tex, float escU, float escV) {
    textura = tex;
    usarTextura = true;
    escalaU = escU;
    escalaV = escV;
}