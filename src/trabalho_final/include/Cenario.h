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
        Camera* camera;
        std::vector<ObjetoAbstrato*> objetos;
        FonteIluminacao fonte;
        Cor cor_background;
        int n_col, n_lin;
        std::vector<unsigned char> canvas;
        ObjetoAbstrato* objetoSelecionado;
        Ponto pontoSelecionado;

        // construtor original (mantém compatibilidade)
        Cenario(Ponto& olho, Janela& janela, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin);
        
        // novo construtor com câmera
        Cenario(Camera* camera, FonteIluminacao& fonte, Cor& background, int n_col, int n_lin);
        
        void adicionarObjeto(ObjetoAbstrato* obj);
        void render();
        void salvarPPM(const std::string& filename);


        // funções que são importantes para interatividade
        bool pick(int mouseX, int mouseY, ObjetoAbstrato*& selecionado, Ponto& pontoImpacto, float& tHit);
        ObjetoAbstrato* getObjetoSelecionado() const;
        Ponto getPontoSelecionado() const;
        void limparSelecao();

        // limpa todos os objetos e a seleção
        void limparObjetos();

        // setter para a fonte de iluminação
        void setFonteIluminacao(const FonteIluminacao& novaFonte) {
            fonte = novaFonte;
        }
};

#endif