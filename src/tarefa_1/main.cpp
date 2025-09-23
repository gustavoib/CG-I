#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

// parametros da janela (em metros)
const float w_janela = 2.0f;   
const float h_janela = 2.0f;   
const float d_janela = 1.0f;

// olho do pintor
const float olho[4] = {0.0f, 0.0f, 0.0f, 1.0f};

// esfera
const float raio_esfera = 0.5f;             
const float centro_esfera[3] = {0.0f, 0.0f, -(d_janela + raio_esfera)};

// cores
const unsigned char cor_intersecao[3] = {255, 0, 0};  // vermelho
const unsigned char cor_background[3] = {100, 100, 100}; // cinza

// tamanho da tela de mosquito (em pixels)
const int n_col = 500;
const int n_lin = 500;

// buffer de cores (canvas)
std::vector<unsigned char> canvas(n_col * n_lin * 3);

// callback para redimensionamento
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

// produto escalar
float produto_escalar(const float a[3], const float b[3]) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

float raio(const float origem[3], const float direcao[3]) {
    float vetor_p_menos_c[3] = {origem[0] - centro_esfera[0], origem[1] - centro_esfera[1], origem[2] - centro_esfera[2]};
    
    float a = produto_escalar(direcao, direcao);
    float b = 2.0f * produto_escalar(vetor_p_menos_c, direcao);
    float c = produto_escalar(vetor_p_menos_c, vetor_p_menos_c) - raio_esfera*raio_esfera;

    float delta = b*b - 4*a*c;

    if (delta < 0) {
        float t = -1.0f;
        return t;
    } else {
        float t1 = (-b - sqrt(delta)) / (2.0f * a);
        float t2 = (-b + sqrt(delta)) / (2.0f * a);

        if (t1 < t2) {
            return t1;
        } else {
            return t2;
        }
    }
}

// funcao para lançar os raios
void render() {
    float delta_x = w_janela / n_col;
    float delta_y = h_janela / n_lin;

    float z = -d_janela;
    for (int l = 0; l < n_lin; l++) {
        float y =  h_janela/2.0f - delta_y/2.0f - l*delta_y;
        for (int c = 0; c < n_col; c++) {
            float x = -w_janela/2.0f + delta_x/2.0f + c*delta_x;

            unsigned char* pixel = &canvas[(l*n_col + c) * 3];
            
            float direcao[3] = {x - olho[0], y - olho[1], z - olho[2]};
            float direcao_normal = sqrt((direcao[0]*direcao[0]) + (direcao[1]*direcao[1]) + (direcao[2]*direcao[2]));
            float d[3] = {direcao[0]/direcao_normal, direcao[1]/direcao_normal, direcao[2]/direcao_normal};
            float delta = raio(olho, d);

            if (delta >= 0) {
                pixel[0] = cor_intersecao[0];
                pixel[1] = cor_intersecao[1];
                pixel[2] = cor_intersecao[2];
            } else {
                pixel[0] = cor_background[0];
                pixel[1] = cor_background[1];
                pixel[2] = cor_background[2];
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

    GLFWwindow* window = glfwCreateWindow(n_col, n_lin, "Tarefa 1", NULL, NULL);
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

    render();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawPixels(n_col, n_lin, GL_RGB, GL_UNSIGNED_BYTE, canvas.data());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}