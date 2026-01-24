#include "include/Menu.h"
#include "include/Cenario.h"
#include "include/Vetor.h"

Menu::Menu() : m_mostrar(true), camera(nullptr), rerenderRequested(false), buffersInitialized(false) {
}

Menu::~Menu() {
}

void Menu::renderizar() {
    if (!m_mostrar || !camera) return;
    
    ImGui::Begin("Configurações");

    // inicializar buffers a partir da câmera apenas uma vez
    if (!buffersInitialized) {
        Ponto eyeInit = camera->getEye();
        Ponto atInit  = camera->getAt();
        Vetor upInit  = camera->getUp();
        eyeBuf[0] = eyeInit.x; eyeBuf[1] = eyeInit.y; eyeBuf[2] = eyeInit.z;
        atBuf [0] = atInit.x;  atBuf [1] = atInit.y;  atBuf [2] = atInit.z;
        upBuf [0] = upInit.x;  upBuf [1] = upInit.y;  upBuf [2] = upInit.z;
        dBuf = camera->getD();
        xminBuf = camera->getXmin();
        xmaxBuf = camera->getXmax();
        yminBuf = camera->getYmin();
        ymaxBuf = camera->getYmax();
        
        if (fonteIluminacao) {
            Ponto fontePos = fonteIluminacao->getPosicao();
            fontePosicaoBuf[0] = fontePos.x;
            fontePosicaoBuf[1] = fontePos.y;
            fontePosicaoBuf[2] = fontePos.z;
        }
        
        buffersInitialized = true;
    }

    if (ImGui::CollapsingHeader("Câmera")) {
        ImGui::InputFloat3("Eye", eyeBuf, "%.2f");
        ImGui::InputFloat3("At",  atBuf,  "%.2f");
        ImGui::InputFloat3("Up",  upBuf,  "%.2f");
    }

    if (ImGui::CollapsingHeader("Projeção")) {
        ImGui::InputFloat("D", &dBuf, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Xmin", &xminBuf, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Xmax", &xmaxBuf, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Ymin", &yminBuf, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Ymax", &ymaxBuf, 0.0f, 0.0f, "%.2f");

        // 1 ponto de fuga
        if (ImGui::Button("1 Ponto de Fuga##1PF", ImVec2(-1, 0))) {
            eyeBuf[0] = 200.0f; eyeBuf[1] = 100.0f; eyeBuf[2] = 100.0f;
            atBuf[0] = 200.0f;  atBuf[1] = 100.0f;  atBuf[2] = 600.0f;
            upBuf[0] = 0.0f;    upBuf[1] = 1.0f;    upBuf[2] = 0.0f;
            dBuf = 300.0f;
            xminBuf = -200.0f;
            xmaxBuf = 200.0f;
            yminBuf = -200.0f;
            ymaxBuf = 200.0f;
            camera->setEye(Ponto(eyeBuf[0], eyeBuf[1], eyeBuf[2]));
            camera->setAt(Ponto(atBuf[0], atBuf[1], atBuf[2]));
            camera->setUp(Vetor(upBuf[0], upBuf[1], upBuf[2]));
            camera->setD(300.0f);
            camera->setXmin(-200.0f);
            camera->setXmax(200.0f);
            camera->setYmin(-200.0f);
            camera->setYmax(200.0f);
            camera->calcularSistemaCoordenadasCamera();
            rerenderRequested = true;
        }
        ImGui::SameLine();
        ImGui::TextDisabled("(frontal)");
        
        // 2 pontos de fuga
        if (ImGui::Button("2 Pontos de Fuga##2PF", ImVec2(-1, 0))) {
            eyeBuf[0] = 350.0f; eyeBuf[1] = 150.0f; eyeBuf[2] = 150.0f;
            atBuf[0] = 200.0f;  atBuf[1] = 100.0f;  atBuf[2] = 400.0f;
            upBuf[0] = 0.0f;    upBuf[1] = 1.0f;    upBuf[2] = 0.0f;
            dBuf = 300.0f;
            xminBuf = -200.0f;
            xmaxBuf = 200.0f;
            yminBuf = -200.0f;
            ymaxBuf = 200.0f;
            camera->setEye(Ponto(eyeBuf[0], eyeBuf[1], eyeBuf[2]));
            camera->setAt(Ponto(atBuf[0], atBuf[1], atBuf[2]));
            camera->setUp(Vetor(upBuf[0], upBuf[1], upBuf[2]));
            camera->setD(300.0f);
            camera->setXmin(-200.0f);
            camera->setXmax(200.0f);
            camera->setYmin(-200.0f);
            camera->setYmax(200.0f);
            camera->calcularSistemaCoordenadasCamera();
            rerenderRequested = true;
        }
        ImGui::SameLine();
        ImGui::TextDisabled("(diagonal)");
        
        // 3 pontos de fuga
        if (ImGui::Button("3 Pontos de Fuga##3PF", ImVec2(-1, 0))) {
            eyeBuf[0] = 400.0f; eyeBuf[1] = 350.0f; eyeBuf[2] = 200.0f;
            atBuf[0] = 200.0f;  atBuf[1] = 100.0f;  atBuf[2] = 300.0f;
            upBuf[0] = -0.2f;   upBuf[1] = 0.9f;    upBuf[2] = 0.3f;
            dBuf = 300.0f;
            xminBuf = -200.0f;
            xmaxBuf = 200.0f;
            yminBuf = -200.0f;
            ymaxBuf = 200.0f;
            camera->setEye(Ponto(eyeBuf[0], eyeBuf[1], eyeBuf[2]));
            camera->setAt(Ponto(atBuf[0], atBuf[1], atBuf[2]));
            camera->setUp(Vetor(upBuf[0], upBuf[1], upBuf[2]));
            camera->setD(300.0f);
            camera->setXmin(-200.0f);
            camera->setXmax(200.0f);
            camera->setYmin(-200.0f);
            camera->setYmax(200.0f);
            camera->calcularSistemaCoordenadasCamera();
            rerenderRequested = true;
        }
        ImGui::SameLine();
        ImGui::TextDisabled("(livre)");
    }

    if (ImGui::CollapsingHeader("Iluminação")) {
        if (cenario && cenario->fontes.size() >= 2) {
            FonteIluminacao* fontep = cenario->fontes[0];
            FonteIluminacao* fontesp = cenario->fontes[1];
            
            // inicializar buffers na primeira renderização
            static bool fontepInit = false, fontespInit = false;
            if (!fontepInit && fontep) {
                Ponto pos1 = fontep->getPosicao();
                fontepPosicaoBuf[0] = pos1.x;
                fontepPosicaoBuf[1] = pos1.y;
                fontepPosicaoBuf[2] = pos1.z;
                fontepIntensidadeBuf[0] = fontep->I_F.r;
                fontepIntensidadeBuf[1] = fontep->I_F.g;
                fontepIntensidadeBuf[2] = fontep->I_F.b;
                fontepAmbienteBuf[0] = fontep->I_A.r;
                fontepAmbienteBuf[1] = fontep->I_A.g;
                fontepAmbienteBuf[2] = fontep->I_A.b;
                fontepInit = true;
            }
            if (!fontespInit && fontesp) {
                Ponto pos2 = fontesp->getPosicao();
                fontespPosicaoBuf[0] = pos2.x;
                fontespPosicaoBuf[1] = pos2.y;
                fontespPosicaoBuf[2] = pos2.z;
                fontespIntensidadeBuf[0] = fontesp->I_F.r;
                fontespIntensidadeBuf[1] = fontesp->I_F.g;
                fontespIntensidadeBuf[2] = fontesp->I_F.b;
                fontespAmbienteBuf[0] = fontesp->I_A.r;
                fontespAmbienteBuf[1] = fontesp->I_A.g;
                fontespAmbienteBuf[2] = fontesp->I_A.b;
                fontespInit = true;
            }
            
            // fonte pontual
            ImGui::Text("Fonte pontual");
            ImGui::InputFloat3("Posição##F1", fontepPosicaoBuf, "%.2f");
            if (ImGui::Button("Aplicar Posição##F1")) {
                fontep->setPosicao(Ponto(fontepPosicaoBuf[0], fontepPosicaoBuf[1], fontepPosicaoBuf[2]));
                rerenderRequested = true;
            }
            ImGui::InputFloat3("Intensidade##F1", fontepIntensidadeBuf, "%.2f");
            if (ImGui::Button("Aplicar Intensidade##F1")) {
                fontep->I_F = Cor(fontepIntensidadeBuf[0], fontepIntensidadeBuf[1], fontepIntensidadeBuf[2]);
                rerenderRequested = true;
            }
            ImGui::InputFloat3("Ambiente##F1", fontepAmbienteBuf, "%.2f");
            if (ImGui::Button("Aplicar Ambiente##F1")) {
                fontep->I_A = Cor(fontepAmbienteBuf[0], fontepAmbienteBuf[1], fontepAmbienteBuf[2]);
                rerenderRequested = true;
            }
            
            ImGui::Separator();
            
            // fonte spot
            ImGui::Text("Fonte spot");
            ImGui::InputFloat3("Posição##F2", fontespPosicaoBuf, "%.2f");
            if (ImGui::Button("Aplicar Posição##F2")) {
                fontesp->setPosicao(Ponto(fontespPosicaoBuf[0], fontespPosicaoBuf[1], fontespPosicaoBuf[2]));
                rerenderRequested = true;
            }
            ImGui::InputFloat3("Intensidade##F2", fontespIntensidadeBuf, "%.2f");
            if (ImGui::Button("Aplicar Intensidade##F2")) {
                fontesp->I_F = Cor(fontespIntensidadeBuf[0], fontespIntensidadeBuf[1], fontespIntensidadeBuf[2]);
                rerenderRequested = true;
            }
        }
    }

    if (ImGui::CollapsingHeader("Objeto Selecionado")) {
        if (cenario && cenario->getObjetoSelecionado()) {
            ObjetoAbstrato* obj = cenario->getObjetoSelecionado();
            
            ImGui::Text("Objeto: %p", (void*)obj);
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Objeto selecionado");
            ImGui::Separator();
            
            // inicializar buffers de cores apenas quando um novo objeto é selecionado
            if (obj != objetoSelecionadoAnterior) {
                corKeBuf[0] = obj->Ke.r; corKeBuf[1] = obj->Ke.g; corKeBuf[2] = obj->Ke.b;
                corKdBuf[0] = obj->Kd.r; corKdBuf[1] = obj->Kd.g; corKdBuf[2] = obj->Kd.b;
                corKaBuf[0] = obj->Ka.r; corKaBuf[1] = obj->Ka.g; corKaBuf[2] = obj->Ka.b;
                // inicializar translação apenas na troca de seleção
                translacaoBuf[0] = obj->getCentro().x;
                translacaoBuf[1] = obj->getCentro().y;
                translacaoBuf[2] = obj->getCentro().z;
                objetoSelecionadoAnterior = obj;
            }
            
            if (ImGui::CollapsingHeader("Cores")) {
                ImGui::ColorEdit3("Ke", corKeBuf);
                ImGui::ColorEdit3("Kd", corKdBuf);
                ImGui::ColorEdit3("Ka", corKaBuf);
                if (ImGui::Button("Aplicar Cores")) {
                    obj->Ke = Cor(corKeBuf[0], corKeBuf[1], corKeBuf[2]);
                    obj->Kd = Cor(corKdBuf[0], corKdBuf[1], corKdBuf[2]);
                    obj->Ka = Cor(corKaBuf[0], corKaBuf[1], corKaBuf[2]);
                    rerenderRequested = true;
                }
            }

            
            if (ImGui::CollapsingHeader("Transformações")) {
                // translação comum (com deslocamento relativo)
                ImGui::InputFloat3("Transladar Rel", translacaoBuf, "%.2f");
                if (ImGui::Button("Aplicar Translação Relativa")) {
                    obj->transladar(translacaoBuf[0], translacaoBuf[1], translacaoBuf[2]);
                    // atualizar buffer para nova posição absoluta
                    Ponto novoCentro = obj->getCentro();
                    translacaoBuf[0] = novoCentro.x;
                    translacaoBuf[1] = novoCentro.y;
                    translacaoBuf[2] = novoCentro.z;
                    rerenderRequested = true;
                }
                
                // translação (posição absoluta)
                ImGui::InputFloat3("Transladar Abs", translacaoBuf, "%.2f");
                if (ImGui::Button("Aplicar Translação Abs")) {
                    // calcular deslocamento relativo necessário
                    Ponto centroAtual = obj->getCentro();
                    float dx = translacaoBuf[0] - centroAtual.x;
                    float dy = translacaoBuf[1] - centroAtual.y;
                    float dz = translacaoBuf[2] - centroAtual.z;
                    obj->transladar(dx, dy, dz);
                    Ponto novoCentro = obj->getCentro();
                    translacaoBuf[0] = novoCentro.x;
                    translacaoBuf[1] = novoCentro.y;
                    translacaoBuf[2] = novoCentro.z;
                    rerenderRequested = true;
                }
                
                ImGui::Spacing();
                
                // escala
                ImGui::InputFloat3("Escala", escalaBuf, "%.2f");
                if (ImGui::Button("Aplicar Escala")) {
                    obj->escalar(escalaBuf[0], escalaBuf[1], escalaBuf[2]);
                    rerenderRequested = true;
                }
                
                ImGui::Spacing();
                
                // rotação
                const char* eixos[] = { "X", "Y", "Z" };
                ImGui::Combo("Eixo", &eixoRotacao, eixos, 3);
                ImGui::InputFloat("Ângulo (graus)", &rotacaoBuf, 0.0f, 0.0f, "%.1f");
                if (ImGui::Button("Aplicar Rotação")) {
                    if (eixoRotacao == 0) obj->rotacionarX(rotacaoBuf);
                    else if (eixoRotacao == 1) obj->rotacionarY(rotacaoBuf);
                    else obj->rotacionarZ(rotacaoBuf);
                    rerenderRequested = true;
                }
                
                ImGui::Spacing();
                
                // rotação Arbitrária
                ImGui::Text("Rotação Arbitrária:");
                ImGui::InputFloat3("Eixo (vetor)", eixoArbitrarioBuf, "%.2f");
                ImGui::InputFloat("Ângulo (graus)##arb", &anguloArbitrarioBuf, 0.0f, 0.0f, "%.1f");
                if (ImGui::Button("Aplicar Rotação Arbitrária")) {
                    Vetor eixo(eixoArbitrarioBuf[0], eixoArbitrarioBuf[1], eixoArbitrarioBuf[2]);
                    obj->rotacionarArbitrario(eixo, anguloArbitrarioBuf);
                    rerenderRequested = true;
                }
                
                ImGui::Spacing();
                
                // cisalhamento
                const char* planos[] = { "XY", "XZ", "YZ" };
                ImGui::Combo("Plano", &planoCisalhamento, planos, 3);
                ImGui::InputFloat2("Cisalhamento", cisalhamentoBuf, "%.2f");
                if (ImGui::Button("Aplicar Cisalhamento")) {
                    if (planoCisalhamento == 0) obj->cisalharXY(cisalhamentoBuf[0], cisalhamentoBuf[1]);
                    else if (planoCisalhamento == 1) obj->cisalharXZ(cisalhamentoBuf[0], cisalhamentoBuf[1]);
                    else obj->cisalharYZ(cisalhamentoBuf[0], cisalhamentoBuf[1]);
                    rerenderRequested = true;
                }
            }
            
            ImGui::Separator();
                        if (ImGui::Button("Limpar Seleção")) {
                cenario->limparSelecao();
                objetoSelecionadoAnterior = nullptr; // resetar flag de seleção
            }
        } else {
            ImGui::Text("Nenhum objeto selecionado");
            ImGui::Text("Clique na cena para selecionar");
        }
    }

    ImGui::Separator();



    if (ImGui::Button("Confirmar")) {
        camera->setEye(Ponto(eyeBuf[0], eyeBuf[1], eyeBuf[2]));
        camera->setAt (Ponto(atBuf[0],  atBuf[1],  atBuf[2]));
        camera->setUp (Vetor(upBuf[0],  upBuf[1],  upBuf[2]));
        camera->setD(dBuf);
        camera->setXmin(xminBuf);
        camera->setXmax(xmaxBuf);
        camera->setYmin(yminBuf);
        camera->setYmax(ymaxBuf);
        camera->calcularSistemaCoordenadasCamera(); // recalc n,u,v
        
        if (fonteIluminacao) {
            fonteIluminacao->setPosicao(Ponto(fontePosicaoBuf[0], fontePosicaoBuf[1], fontePosicaoBuf[2]));
        }
        
        rerenderRequested = true;
    }
    
    ImGui::End();
}

bool Menu::mostrarMenu() const {
    return m_mostrar;
}