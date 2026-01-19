#ifndef MENU_H
#define MENU_H

#include "../../../include/imgui/imgui.h"
#include "Camera.h"

class Menu {
public:
    Menu();
    ~Menu();
    
    void setCamera(Camera* cam) {
        camera = cam;
    }
    
    bool needsRerender() const { return rerenderRequested; }
    void clearRerenderFlag() { rerenderRequested = false; }
    void renderizar();  // Desenha o menu
    
    // Getters para os valores controlados pelo menu
    bool mostrarMenu() const;
    // Adicione outras propriedades conforme necessário
    
private:
    bool m_mostrar;
    Camera* camera = nullptr;
    bool rerenderRequested = false;
    bool buffersInitialized = false;
    float eyeBuf[3] = {0.0f, 0.0f, 0.0f};
    float atBuf[3]  = {0.0f, 0.0f, 0.0f};
    float upBuf[3]  = {0.0f, 0.0f, 0.0f};
};

#endif