#ifndef CENARIO_H
#define CENARIO_H

#include <vector>
#include <string>
#include "ObjetoAbstrato.h"
#include "FonteIluminacao.h"
#include "Janela.h"
#include "Camera.h"
#include "Ponto.h"
#include "Cor.h"

class Cenario {
    public:
        Ponto olho;
        Janela janela;
        Camera* camera;  // Adiciona ponteiro para câmera
        std::vector<ObjetoAbstrato*> objetos;
        FonteIluminacao fonte;
        Cor cor_background;
        int n_col, n_lin;
        std::vector<unsigned char> canvas;

        // Construtor original (mantém compatibilidade)
        Cenario(Ponto& olho, Janela& janela, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin);
        
        // Novo construtor com câmera
        Cenario(Camera* camera, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin);
        
        void adicionarObjeto(ObjetoAbstrato* obj);
        void render();
        void salvarPPM(const std::string& filename);
};

#endif