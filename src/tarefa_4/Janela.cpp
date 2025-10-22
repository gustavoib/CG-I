#include "Janela.h"

Janela::Janela(float largura, float altura, float distancia) : w_janela(largura), h_janela(altura), d_janela(distancia) {}

float Janela::menosDJanela() {
    return -d_janela;
}