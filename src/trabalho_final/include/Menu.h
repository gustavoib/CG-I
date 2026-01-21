#ifndef MENU_H
#define MENU_H

#include "../../../include/imgui/imgui.h"
#include "Camera.h"
#include "FonteIluminacao.h"

class Cenario;
class ObjetoAbstrato;

class Menu {
public:
    Menu();
    ~Menu();
    
    void setCamera(Camera* cam) {
        camera = cam;
    }

    void setFonteIluminacao(FonteIluminacao* fonte) {
        fonteIluminacao = fonte;
    }

    void setCenario(Cenario* cen) {
        cenario = cen;
    }
    
    bool needsRerender() const { return rerenderRequested; }
    void clearRerenderFlag() { rerenderRequested = false; }
    void renderizar();  // Desenha o menu
    
    bool mostrarMenu() const;
    
private:
    bool m_mostrar;
    Camera* camera = nullptr;
    FonteIluminacao* fonteIluminacao = nullptr;
    Cenario* cenario = nullptr;
    bool rerenderRequested = false;
    bool buffersInitialized = false;
    float eyeBuf[3] = {0.0f, 0.0f, 0.0f};
    float atBuf[3]  = {0.0f, 0.0f, 0.0f};
    float upBuf[3]  = {0.0f, 0.0f, 0.0f};
    float dBuf = 0.0f;
    float xminBuf = 0.0f;
    float xmaxBuf = 0.0f;
    float yminBuf = 0.0f;
    float ymaxBuf = 0.0f;
    float fontePosicaoBuf[3] = {0.0f, 0.0f, 0.0f};
    
    // buffers para transformações
    float translacaoBuf[3] = {0.0f, 0.0f, 0.0f};
    float escalaBuf[3] = {1.0f, 1.0f, 1.0f};
    float rotacaoBuf = 0.0f;
    int eixoRotacao = 0; // 0=X, 1=Y, 2=Z
    float eixoArbitrarioBuf[3] = {0.0f, 1.0f, 0.0f}; // vetor eixo arbitrário
    float anguloArbitrarioBuf = 0.0f;
    float cisalhamentoBuf[2] = {0.0f, 0.0f};
    int planoCisalhamento = 0; // 0=XY, 1=XZ, 2=YZ
    
    // buffers para cores
    float corKeBuf[3] = {0.0f, 0.0f, 0.0f}; 
    float corKdBuf[3] = {0.0f, 0.0f, 0.0f};
    float corKaBuf[3] = {0.0f, 0.0f, 0.0f};
    ObjetoAbstrato* objetoSelecionadoAnterior = nullptr; // para detectar mudança de seleção
};

#endif