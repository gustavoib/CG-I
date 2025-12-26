#ifndef TEXTURA_H
#define TEXTURA_H

#include "Cor.h"
#include <string>
#include <vector>

class Textura {
private:
    std::vector<std::vector<Cor>> pixels;
    int largura;
    int altura;
    
public:
    Textura();
    Textura(int largura, int altura);
    
    bool carregarImagem(const std::string& caminho);
    bool carregarPPM(const std::string& arquivo);
    void gerarTexturaMadeira(int largura, int altura);
    
    Cor obterCor(float u, float v) const;
    
    int getLargura() const { return largura; }
    int getAltura() const { return altura; }
};

#endif