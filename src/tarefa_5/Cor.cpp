#include "include/Cor.h"
#include <algorithm>
#include <iostream>

using namespace std;

Cor::Cor(float r, float g, float b) : r(r), g(g), b(b) {}

Cor Cor::somarCor(Cor& c) {
    return Cor(r + c.r, g + c.g, b + c.b);
}

Cor Cor::multiEscalar(float t) {
    return Cor(r*t, g*t, b*t);
}

Cor Cor::multiComponente(Cor& c) {
    return Cor(r*c.r, g*c.g, b*c.b);
}

void Cor::limitar() {
    r = min(1.0f, max(0.0f, r));
    g = min(1.0f, max(0.0f, g));
    b = min(1.0f, max(0.0f, b));
}

void Cor::escreverNoBuffer(unsigned char* pixel) {
    pixel[0] = r*255.0f;
    pixel[1] = g*255.0f;
    pixel[2] = b*255.0f;
}