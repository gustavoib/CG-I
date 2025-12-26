#ifndef CENARIO_H
#define CENARIO_H

#include <vector>
#include <string>
#include "ObjetoAbstrato.h"
#include "FonteIluminacao.h"
#include "Janela.h"
#include "Ponto.h"
#include "Cor.h"

class Cenario {
    public:
        Ponto olho;
        Janela janela;
        std::vector<ObjetoAbstrato*> objetos;
        FonteIluminacao fonte;
        Cor cor_background;
        int n_col, n_lin;
        std::vector<unsigned char> canvas;

        Cenario(Ponto& olho, Janela& janela, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin);
        
        void adicionarObjeto(ObjetoAbstrato* obj);
        void render();
        void salvarPPM(const std::string& filename);
};

#endif