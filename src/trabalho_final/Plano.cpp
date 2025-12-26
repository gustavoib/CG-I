#include "../tarefa_5/include/Plano.h"
#include "../tarefa_5/include/Textura.h"
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

Cor Plano::calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
    Vetor vetor_n = n;
    
    Vetor v = direcao_raio.vetorNegativo();
    
    Vetor l = fonte.P_F.subPonto(Pi).normalizado();
    
    float produto_nl_limitado = max(0.0f, vetor_n.produtoEscalar(l));
    Vetor r = vetor_n.multiEscalar(2.0f * produto_nl_limitado).subVetor(l);
    
    Cor corDifusa = obterCorDifusa(Pi);
    
    Cor IFKd = fonte.I_F.multiComponente(corDifusa);
    Cor I_d = IFKd.multiEscalar(produto_nl_limitado);

    Cor IFKe = fonte.I_F.multiComponente(Ke);    
    float produto_vr = max(0.0f, v.produtoEscalar(r));
    Cor I_e = IFKe.multiEscalar(pow(produto_vr, this->m));

    Cor I_a = fonte.I_A.multiComponente(Ka);
    
    Cor IdIe = I_d.somarCor(I_e);
    Cor IE = IdIe.somarCor(I_a);
    
    IE.limitar();
    
    return IE;
}

void Plano::setTextura(std::shared_ptr<Textura> tex, float escU, float escV) {
    textura = tex;
    usarTextura = true;
    escalaU = escU;
    escalaV = escV;
}