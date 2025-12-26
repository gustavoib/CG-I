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