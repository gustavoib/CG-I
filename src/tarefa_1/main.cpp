#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

// parametros da janela (em metros)
const float wJanela = 2.0f;   // largura
const float hJanela = 2.0f;   // altura
const float dJanela = 1.0f;   // distância do olho até a janela

// olho do pintor
const float olho[3] = {0.0f, 0.0f, 0.0f};

// esfera
const float rEsfera = 1.0f;             
const float esfCentro[3] = {0.0f, 0.0f, -(dJanela + rEsfera)}; // centro no eixo z (atrás da janela)
const unsigned char esfColor[3] = {255, 0, 0};  // vermelho

// background
const unsigned char bgColor[3] = {100, 100, 100}; // cinza

// tamanho da tela de mosquito (em pixels)
const int nCol = 600;
const int nLin = 600;

// buffer de cores (canvas)
std::vector<unsigned char> canvas(nCol * nLin * 3);

// callback para redimensionamento
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

// produto escalar
float dot(const float a[3], const float b[3]) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

float raio(const float origem[3], const float direcao[3]) {
    float oc[3] = {origem[0] - esfCentro[0],
                   origem[1] - esfCentro[1],
                   origem[2] - esfCentro[2]};
    
    float a = dot(direcao, direcao);
    float b = 2.0f * dot(oc, direcao);
    float c = dot(oc, oc) - rEsfera*rEsfera;

    float delta = b*b - 4*a*c;

    if (delta < 0) {
        float t = -1.0f;
        return t;
    } else {
        float t = (-b - sqrt(delta)) / (2.0f * a);
        return t;
    }
}

// funcao para lançar os raios
void renderScene() {
    float Dx = wJanela / nCol;
    float Dy = hJanela / nLin;

    float z = -dJanela;
    for (int l = 0; l < nLin; l++) {
        float y =  hJanela/2.0f - Dy/2.0f - l*Dy;
        for (int c = 0; c < nCol; c++) {
            float x = -wJanela/2.0f + Dx/2.0f + c*Dx;

            unsigned char* pixel = &canvas[(l*nCol + c) * 3];

            float delta = raio(olho, (float[3]){x - olho[0], y - olho[1], z - olho[2]});

            if (delta >= 0) {
                // Raio bateu na esfera
                pixel[0] = esfColor[0];
                pixel[1] = esfColor[1];
                pixel[2] = esfColor[2];
            } else {
                // Background
                pixel[0] = bgColor[0];
                pixel[1] = bgColor[1];
                pixel[2] = bgColor[2];
            }
        }
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Erro ao inicializar GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(nCol, nLin, "Ray Casting - Esfera", NULL, NULL);
    if (!window) {
        std::cerr << "Erro ao criar janela GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erro ao inicializar GLAD\n";
        return -1;
    }

    renderScene();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawPixels(nCol, nLin, GL_RGB, GL_UNSIGNED_BYTE, canvas.data());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}