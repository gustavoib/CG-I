#ifndef JANELA_H
#define JANELA_H

class Janela {
public:
    float w_janela, h_janela, d_janela;

    Janela(float largura, float altura, float distancia);
    float menosDJanela();
};

#endif