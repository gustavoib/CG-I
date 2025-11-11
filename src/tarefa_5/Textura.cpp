#include "Textura.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Textura::Textura() : largura(0), altura(0) {}

Textura::Textura(int largura, int altura) : largura(largura), altura(altura) {
    pixels.resize(altura, std::vector<Cor>(largura, Cor(0, 0, 0)));
}

bool Textura::carregarImagem(const std::string& caminho) {
    int canais;
    unsigned char* data = stbi_load(caminho.c_str(), &largura, &altura, &canais, 3);
    
    if (!data) {
        std::cerr << "Erro ao carregar textura: " << caminho << std::endl;
        std::cerr << "Motivo: " << stbi_failure_reason() << std::endl;
        return false;
    }
    
    std::cout << "Carregando textura: " << caminho << " (" << largura << "x" << altura << ", " << canais << " canais)" << std::endl;
    
    // Redimensiona o vetor de pixels
    pixels.resize(altura);
    for (int i = 0; i < altura; i++) {
        pixels[i].resize(largura);
    }
    
    // Converte os dados para o formato Cor (normaliza de 0-255 para 0.0-1.0)
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int index = (y * largura + x) * 3;
            pixels[y][x] = Cor(
                data[index] / 255.0f,
                data[index + 1] / 255.0f,
                data[index + 2] / 255.0f
            );
        }
    }
    
    stbi_image_free(data);
    std::cout << "Textura carregada com sucesso!" << std::endl;
    return true;
}

bool Textura::carregarPPM(const std::string& arquivo) {
    std::ifstream file(arquivo, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    std::string formato;
    file >> formato;
    
    if (formato != "P3" && formato != "P6") {
        return false;
    }
    
    // Ignora comentários
    std::string linha;
    std::getline(file, linha);
    while (file.peek() == '#') {
        std::getline(file, linha);
    }
    
    file >> largura >> altura;
    int maxVal;
    file >> maxVal;
    
    pixels.resize(altura, std::vector<Cor>(largura));
    
    if (formato == "P3") {
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                int r, g, b;
                file >> r >> g >> b;
                pixels[i][j] = Cor(r / 255.0f, g / 255.0f, b / 255.0f);
            }
        }
    }
    
    file.close();
    return true;
}

void Textura::gerarTexturaMadeira(int w, int h) {
    largura = w;
    altura = h;
    pixels.resize(altura, std::vector<Cor>(largura));

    Cor madeira_escura(0.4f, 0.2f, 0.1f);
    Cor madeira_clara(0.6f, 0.4f, 0.2f);
    
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            float x = j / (float)largura;
            float y = i / (float)altura;
            
            float distancia = std::sqrt((x - 0.5f) * (x - 0.5f) + 
                                       (y - 0.5f) * (y - 0.5f) * 4.0f);
            
            float ruido = std::sin(x * 50.0f) * 0.05f + 
                         std::sin(y * 30.0f) * 0.03f;
            
            float padrao = std::sin((distancia + ruido) * 20.0f) * 0.5f + 0.5f;
            
            float t = padrao;
            pixels[i][j] = Cor(
                madeira_escura.r * (1 - t) + madeira_clara.r * t,
                madeira_escura.g * (1 - t) + madeira_clara.g * t,
                madeira_escura.b * (1 - t) + madeira_clara.b * t
            );
            
            float variacao = (std::sin(x * 100.0f + y * 100.0f) * 0.1f + 1.0f);
            pixels[i][j].r *= variacao;
            pixels[i][j].g *= variacao;
            pixels[i][j].b *= variacao;
            
            pixels[i][j].r = std::max(0.0f, std::min(1.0f, pixels[i][j].r));
            pixels[i][j].g = std::max(0.0f, std::min(1.0f, pixels[i][j].g));
            pixels[i][j].b = std::max(0.0f, std::min(1.0f, pixels[i][j].b));
        }
    }
}

Cor Textura::obterCor(float u, float v) const {
    if (pixels.empty()) {
        return Cor(1, 1, 1);
    }

    u = u - std::floor(u);
    v = v - std::floor(v);

    int x = static_cast<int>(u * (largura - 1));
    int y = static_cast<int>(v * (altura - 1));

    x = std::max(0, std::min(largura - 1, x));
    y = std::max(0, std::min(altura - 1, y));
    
    return pixels[y][x];
}