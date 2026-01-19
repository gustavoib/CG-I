#include "include/Menu.h"

Menu::Menu() : m_mostrar(true), camera(nullptr), rerenderRequested(false), buffersInitialized(false) {
}

Menu::~Menu() {
}

void Menu::renderizar() {
    if (!m_mostrar || !camera) return;
    
    ImGui::Begin("Configurações");

    // Inicializar buffers a partir da câmera apenas uma vez
    if (!buffersInitialized) {
        Ponto eyeInit = camera->getEye();
        Ponto atInit  = camera->getAt();
        Vetor upInit  = camera->getUp();
        eyeBuf[0] = eyeInit.x; eyeBuf[1] = eyeInit.y; eyeBuf[2] = eyeInit.z;
        atBuf [0] = atInit.x;  atBuf [1] = atInit.y;  atBuf [2] = atInit.z;
        upBuf [0] = upInit.x;  upBuf [1] = upInit.y;  upBuf [2] = upInit.z;
        buffersInitialized = true;
    }

    ImGui::InputFloat3("Eye", eyeBuf, "%.2f");
    ImGui::InputFloat3("At",  atBuf,  "%.2f");
    ImGui::InputFloat3("Up",  upBuf,  "%.2f");

    if (ImGui::Button("Confirmar")) {
        camera->setEye(Ponto(eyeBuf[0], eyeBuf[1], eyeBuf[2]));
        camera->setAt (Ponto(atBuf[0],  atBuf[1],  atBuf[2]));
        camera->setUp (Vetor(upBuf[0],  upBuf[1],  upBuf[2]));
        camera->calcularSistemaCoordenadasCamera(); // recalc n,u,v
        rerenderRequested = true;
    }
    
    ImGui::End();
}

bool Menu::mostrarMenu() const {
    return m_mostrar;
}