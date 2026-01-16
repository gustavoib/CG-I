#include "../trabalho_final/include/Cenario.h"
#include "../trabalho_final/include/Esfera.h"
#include "../trabalho_final/include/Plano.h"
#include "../trabalho_final/include/FonteIluminacao.h"
#include "../trabalho_final/include/Janela.h"
#include "../trabalho_final/include/Camera.h"
#include "../trabalho_final/include/Ponto.h"
#include "../trabalho_final/include/Vetor.h"
#include "../trabalho_final/include/Cilindro.h"
#include "../trabalho_final/include/Cone.h"
#include "../trabalho_final/include/Cubo.h"
#include "../trabalho_final/include/Textura.h"
#include "../trabalho_final/include/Matriz.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Função para carregar código do shader de arquivo
std::string loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo de shader: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

#define M_PI 3.14159265358979323846

int main() {   
    // sistema antigo
    // Ponto olho(0.0f, 0.0f, -5.0f);
    // Janela janela(60.0f, 60.0f, -30.0f); 
    
    // testes com câmera
    Ponto eye(0.0f, 0.0f, -5.0f);
    Ponto at(0.0f, 0.0f, -100.0f);
    Vetor up(0.0f, 1.0f, 0.0f);
    Camera* camera = new Camera(eye, at, up, 30.0f, -30.0f, 30.0f, -30.0f, 30.0f);
    
    Cor I_F(0.7f, 0.7f, 0.7f);
    Cor I_A(0.3f, 0.3f, 0.3f);
    Ponto P_F(0.0f, 140.0f, -100.0f);
    FonteIluminacao fonte(I_F, P_F, I_A);
    
    Cor cor_background(100.0f/255.0f, 100.0f/255.0f, 100.0f/255.0f);
    
    // com câmera
    Cenario cenario(camera, fonte, cor_background, 500, 500);
    
    // sem câmera
    // Cenario cenario(olho, janela, fonte, cor_background, 500, 500);
    
    //textura
    auto texturaMadeira = std::make_shared<Textura>();
    texturaMadeira->carregarImagem("../src/trabalho_final/img/textura.jpg");

    // plano de frontal
    Ponto P_pif(200.0f, 150.0f, -400.0f);
    Vetor n_barf(0.0f, 0.0f, 1.0f);  // Normal apontando para cima
    Cor kd_planof(0.686f, 0.933f, 0.933f);
    Cor ke_planof(0.686f, 0.933f, 0.933f);
    Cor ka_planof(0.686f, 0.933f, 0.933f);
    float m_planof = 50.0f;

    // lateral direita
    Ponto P_pid(200.0f, -150.0f, 0.0f);
    Vetor n_bard(-1.0f, 0.0f, 0.0f);  // Normal apontando para cima
    Cor kd_planod(0.686f, 0.933f, 0.933f);
    Cor ke_planod(0.686f, 0.933f, 0.933f);
    Cor ka_planod(0.686f, 0.933f, 0.933f);
    float m_planod = 50.0f;

    // lateral esquerda
    Ponto P_pie(-200.0f, -150.0f, 0.0f);
    Vetor n_bare(1.0f, 0.0f, 0.0f);  // Normal apontando para cima
    Cor kd_planoe(0.686f, 0.933f, 0.933f);
    Cor ke_planoe(0.686f, 0.933f, 0.933f);
    Cor ka_planoe(0.686f, 0.933f, 0.933f);
    float m_planoe = 50.0f;

    // plano do chão
    Ponto P_pic(0.0f, -150.0f, 0.0f);
    Vetor n_barc(0.0f, 1.0f, 0.0f); 
    float m_planoc = 50.0f;

    // plano do teto
    Ponto P_pit(0.0f, 150.0f, 0.0f);
    Vetor n_bart(0.0f, -1.0f, 0.0f); 
    Cor kd_planot(0.933f, 0.933f, 0.933f);
    Cor ke_planot(0.933f, 0.933f, 0.933f);
    Cor ka_planot(0.933f, 0.933f, 0.933f);
    float m_planot = 50.0f;

    Plano* plano_frontal = new Plano(n_barf, P_pif, ke_planof, kd_planof, ka_planof, m_planof);
    cenario.adicionarObjeto(plano_frontal);

    Plano* plano_chao = new Plano(n_barc, P_pic, texturaMadeira, 0.2f, 0.2f, m_planoc);
    cenario.adicionarObjeto(plano_chao);

    Plano* plano_direita = new Plano(n_bard, P_pid, ke_planod, kd_planod, ka_planod, m_planod);
    cenario.adicionarObjeto(plano_direita);

    Plano* plano_esquerda = new Plano(n_bare, P_pie, ke_planoe, kd_planoe, ka_planoe, m_planoe);
    cenario.adicionarObjeto(plano_esquerda);

    Plano* plano_teto = new Plano(n_bart, P_pit, ke_planot, kd_planot, ka_planot, m_planot);
    cenario.adicionarObjeto(plano_teto);

    // mockup do cenário imaginado

    // cama
    float aresta_cubo = 100.0f;
    Ponto centro_cubo(0.0f, -160.0f, -320.0f);
    Cor kd_cubo(1.0f, 0.0f, 0.0f);
    Cor ke_cubo(1.0f, 0.0f, 0.0f);
    Cor ka_cubo(1.0f, 0.0f, 0.0f);
    float m_cubo = 10.0f;

    Cubo cubo;
    Malha* malha = new Malha(cubo.criarCubo(centro_cubo, aresta_cubo, ke_cubo, kd_cubo, ka_cubo, m_cubo));
    malha->escalar(1.0f, 0.3f, 1.5f); // para criar a cama
    cenario.adicionarObjeto(malha);

    // travesseiro
    float aresta_travesseiro = 30.0f;
    Ponto centro_travesseiro(0.0f, -105.0f, -380.0f);
    Cor kd_travesseiro(1.0f, 1.0f, 1.0f);
    Cor ke_travesseiro(1.0f, 1.0f, 1.0f);
    Cor ka_travesseiro(1.0f, 1.0f, 1.0f);
    float m_travesseiro = 10.0f;

    Cubo cubo_travesseiro;
    Malha* malha_travesseiro = new Malha(cubo_travesseiro.criarCubo(centro_travesseiro, aresta_travesseiro, ke_travesseiro, kd_travesseiro, ka_travesseiro, m_travesseiro));
    malha_travesseiro->escalar(2.0f, 0.3f, 1.0f); // para criar o travesseiro
    cenario.adicionarObjeto(malha_travesseiro);

    // pé 1 - cama
    Ponto cb_pe1(40.0f, -157.5f, -250.0f);
    Ponto p1 = cb_pe1;
    float rb_pe1 = 5.0f;
    float H_cilindro = 30.0f;
    Vetor dc(0.0f, 1.0f, 0.0f);
    Cor kd_c(0.396f, 0.263f, 0.129f);
    Cor ke_c(0.396f, 0.263f, 0.129f);
    Cor ka_c(0.396f, 0.263f, 0.129f);

    Cilindro* pe1 = new Cilindro(p1, cb_pe1, dc, H_cilindro, rb_pe1, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe1);

    // pé 2 - cama
    Ponto cb_pe2(-40.0f, -157.5f, -250.0f);
    Ponto p2 = cb_pe2;
    float raio_base = 5.0f;

    Cilindro* pe2 = new Cilindro(p2, cb_pe2, dc, H_cilindro, raio_base, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe2);

    // pé 3 - cama
    Ponto cb_pe3(40.0f, -157.5f, -390.0f);
    Ponto p3 = cb_pe3;
    float raio_base3 = 5.0f;

    Cilindro* pe3 = new Cilindro(p3, cb_pe3, dc, H_cilindro, raio_base3, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe3);

    // pé 4 - cama
    Ponto cb_pe4(-40.0f, -157.5f, -390.0f);
    Ponto p4 = cb_pe4;
    float raio_base4 = 5.0f;

    Cilindro* pe4 = new Cilindro(p4, cb_pe4, dc, H_cilindro, raio_base4, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe4);

    // mesa de cabeceira
    float aresta_mesa = 10.0f;
    Ponto centro_mesa(120.0f, -90.0f, -300.0f);
    Cor kd_mesa(0.396f, 0.263f, 0.129f);
    Cor ke_mesa(0.396f, 0.263f, 0.129f);
    Cor ka_mesa(0.396f, 0.263f, 0.129f);
    float m_mesa = 10.0f;

    Cubo cubo_mesa;
    Malha* malha_mesa = new Malha(cubo_mesa.criarCubo(centro_mesa, aresta_mesa, ke_mesa, kd_mesa, ka_mesa, m_mesa));
    malha_mesa->escalar(10.0f, 1.0f, 10.0f);
    cenario.adicionarObjeto(malha_mesa);

    // pé 1 - mesa de cabeceira
    float H_pe_mesa = 60.0f;
    Ponto cb_pe_mesa1(80.0f, -150.0f, -260.0f);
    Ponto p_pe_mesa1 = cb_pe_mesa1;
    float rb_pe_mesa = 5.0f;
    
    Cilindro* pe_mesa1 = new Cilindro(p_pe_mesa1, cb_pe_mesa1, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa1);

    // pé 2 - mesa de cabeceira
    Ponto cb_pe_mesa2(160.0f, -150.0f, -260.0f);
    Ponto p_pe_mesa2 = cb_pe_mesa2;

    Cilindro* pe_mesa2 = new Cilindro(p_pe_mesa2, cb_pe_mesa2, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa2);

    // pé 3 - mesa de cabeceira
    Ponto cb_pe_mesa3(80.0f, -150.0f, -340.0f);
    Ponto p_pe_mesa3 = cb_pe_mesa3;

    Cilindro* pe_mesa3 = new Cilindro(p_pe_mesa3, cb_pe_mesa3, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa3);

    // pé 4 - mesa de cabeceira
    Ponto cb_pe_mesa4(160.0f, -150.0f, -340.0f);
    Ponto p_pe_mesa4 = cb_pe_mesa4;

    Cilindro* pe_mesa4 = new Cilindro(p_pe_mesa4, cb_pe_mesa4, dc, H_pe_mesa, rb_pe_mesa, false, false, ke_c, kd_c, ka_c, 10);
    cenario.adicionarObjeto(pe_mesa4);

    // arvore na mesa

    // jarro (cilindro)
    Ponto cb_jarro(120.0f, -80.0f, -300.0f);
    Ponto p_jarro = cb_jarro;
    float rb_jarro = 8.0f;
    float H_jarro_cilindro = 20.0f;
    Cor kd_jarro(0.650f, 0.200f, 0.200f);
    Cor ke_jarro(0.650f, 0.200f, 0.200f);
    Cor ka_jarro(0.650f, 0.200f, 0.200f);
    
    Cilindro* jarro_base = new Cilindro(p_jarro, cb_jarro, dc, H_jarro_cilindro, rb_jarro, true, true, ke_jarro, kd_jarro, ka_jarro, 10);
    cenario.adicionarObjeto(jarro_base);

    // caule (cilindro)
    Ponto cb_caule(120.0f, -70.0f, -300.0f);
    Ponto p_caule = cb_caule;
    float rb_caule = 3.0f;
    float H_caule = 30.0f;
    Cor kd_caule(0.396f, 0.263f, 0.129f);
    Cor ke_caule(0.396f, 0.263f, 0.129f);
    Cor ka_caule(0.396f, 0.263f, 0.129f);

    Cilindro* abajur_caule = new Cilindro(p_caule, cb_caule, dc, H_caule, rb_caule, false, false, ke_caule, kd_caule, ka_caule, 10);
    cenario.adicionarObjeto(abajur_caule);

    // folhas (cone)
    Ponto Cb_folhas(120.0f, -50.0f, -300.0f); // centro da base do cone
    float raio_base_cone = 15.0f;
    float H_cone = 35.0f;
    Vetor d_cone(0.0f, 1.0f, 0.0f);
    Cor kd_cone(0.0f, 0.800f, 0.200f);
    Cor ke_cone(0.0f, 0.800f, 0.200f);
    Cor ka_cone(0.0f, 0.800f, 0.200f);
    float theta = atan(raio_base_cone/H_cone);
    Ponto ponto_p_cone = Cb_folhas;
    
    Cone* folhas = new Cone(ponto_p_cone, Cb_folhas, d_cone, theta, H_cone, raio_base_cone, true, ke_cone, kd_cone, ka_cone, 10);
    cenario.adicionarObjeto(folhas);

    // estante na parede
    float aresta_estante = 50.0f;
    Ponto centro_estante(0.0f, 0.0f, -390.0f);
    Cor kd_estante(0.396f, 0.263f, 0.129f);
    Cor ke_estante(0.396f, 0.263f, 0.129f);
    Cor ka_estante(0.396f, 0.263f, 0.129f);
    float m_estante = 10.0f;

    Cubo cubo_estante;
    Malha* malha_estante = new Malha(cubo_estante.criarCubo(centro_estante, aresta_estante, ke_estante, kd_estante, ka_estante, m_estante));
    malha_estante->escalar(3.0f, 0.1f, 1.0f); // para criar a estante
    cenario.adicionarObjeto(malha_estante);

    // esferas decorativas na estante
    float raio_esfera_decorativa = 7.0f;
    Ponto centro_esfera_decorativa1(-50.0f, 33.0f, -390.0f);
    Ponto centro_esfera_decorativa2(0.0f, 33.0f, -390.0f);
    Ponto centro_esfera_decorativa3(50.0f, 33.0f, -390.0f);
    Cor ke_esfera_decorativa(0.125f, 0.498f, 1.0f);
    Cor kd_esfera_decorativa(0.125f, 0.498f, 1.0f);
    Cor ka_esfera_decorativa(0.125f, 0.498f, 1.0f);
    float m_esfera_decorativa = 10.0f;

    Esfera* esfera_decorativa1 = new Esfera(raio_esfera_decorativa, centro_esfera_decorativa1, ke_esfera_decorativa, kd_esfera_decorativa, ka_esfera_decorativa, m_esfera_decorativa);
    cenario.adicionarObjeto(esfera_decorativa1);

    Esfera* esfera_decorativa2 = new Esfera(raio_esfera_decorativa, centro_esfera_decorativa2, ke_esfera_decorativa, kd_esfera_decorativa, ka_esfera_decorativa, m_esfera_decorativa);
    cenario.adicionarObjeto(esfera_decorativa2);
    
    Esfera* esfera_decorativa3 = new Esfera(raio_esfera_decorativa, centro_esfera_decorativa3, ke_esfera_decorativa, kd_esfera_decorativa, ka_esfera_decorativa, m_esfera_decorativa);
    cenario.adicionarObjeto(esfera_decorativa3);

    // lixeira do outro lado da cama (cilindro)
    Ponto cb_lixeira( -150.0f, -150.0f, -380.0f);
    Ponto p_lixeira = cb_lixeira;
    float rb_lixeira = 20.0f;
    float H_lixeira = 40.0f;
    Cor kd_lixeira(0.5f, 0.5f, 0.5f);
    Cor ke_lixeira(0.5f, 0.5f, 0.5f);
    Cor ka_lixeira(0.5f, 0.5f, 0.5f);

    Cilindro* lixeira = new Cilindro(p_lixeira, cb_lixeira, dc, H_lixeira, rb_lixeira, true, false, ke_lixeira, kd_lixeira, ka_lixeira, 10);
    cenario.adicionarObjeto(lixeira);

    // esfera
    // float raio_esfera = 5.0f;
    // Ponto centro_esfera(0.0f, 95.0f, -200.0f);
    // Cor ke_esfera(0.854f, 0.647f, 0.125f);
    // Cor kd_esfera(0.854f, 0.647f, 0.125f);
    // Cor ka_esfera(0.854f, 0.647f, 0.125f);
    // float m_esfera = 10.0f;
    
    // Esfera* esfera = new Esfera(raio_esfera, centro_esfera, ke_esfera, kd_esfera, ka_esfera, m_esfera);
    // cenario.adicionarObjeto(esfera);

    // cilindro
    // Ponto centro_base(0.0f, -150.0f, -200.0f);
    // Ponto ponto_p = centro_base;
    // float raio_base = 5.0f;
    // float H_cilindro = 90.0f;
    // Vetor dc(0.0f, 1.0f, 0.0f);
    // Cor kd_c(0.824f, 0.706f, 0.549f);
    // Cor ke_c(0.824f, 0.706f, 0.549f);
    // Cor ka_c(0.824f, 0.706f, 0.549f);

    // Cilindro* cilindro = new Cilindro(ponto_p, centro_base, dc, H_cilindro, raio_base, false, false, ke_c, kd_c, ka_c, 10);
    // cenario.adicionarObjeto(cilindro);

    // cone
    // Ponto Cb(0.0f, -60.0f, -200.0f); // centro da base do cone
    // float raio_base_cone = 90.0f;
    // float H_cone = 150.0f;
    // Vetor d_cone(0.0f, 1.0f, 0.0f);
    // Cor kd_cone(0.0f, 1.0f, 0.498f);
    // Cor ke_cone(0.0f, 1.0f, 0.498f);
    // Cor ka_cone(0.0f, 1.0f, 0.498f);
    // float theta = atan(raio_base_cone/H_cone);
    // Ponto ponto_p_cone = Cb;

    // Cone* cone = new Cone(ponto_p_cone, Cb, d_cone, theta, H_cone, raio_base_cone, false, ke_cone, kd_cone, ka_cone, 10);
    // cenario.adicionarObjeto(cone);

    // cubo
    // float aresta_cubo = 40.0f;
    // Ponto centro_cubo(0.0f, -150.0f, -165.0f);
    // Cor kd_cubo(1.0f, 0.078f, 0.576f);
    // Cor ke_cubo(1.0f, 0.078f, 0.576f);
    // Cor ka_cubo(1.0f, 0.078f, 0.576f);
    // float m_cubo = 10.0f;

    // Cubo cubo;
    // Malha* malha = new Malha(cubo.criarCubo(centro_cubo, aresta_cubo, ke_cubo, kd_cubo, ka_cubo, m_cubo));
    // cenario.adicionarObjeto(malha);

    // renderizar a cena (preenche o canvas)
    cenario.render();


    // GLFW ----------------------------------------------------------------------------------------------------------------------------
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }

    // criar janela GLFW
    GLFWwindow* window = glfwCreateWindow(cenario.n_col, cenario.n_lin, "Trabalho final CG", NULL, NULL);
    if (!window) {
        std::cerr << "Falha ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    // compilar shaders
    std::string vertexShaderSource = loadShaderSource("../src/trabalho_final/shaders/vertex_shader.glsl");
    std::string fragmentShaderSource = loadShaderSource("../src/trabalho_final/shaders/fragment_shader.glsl");

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vss = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fss = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fss, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -1.0f,  1.0f, 0.0f, 0.0f,  // Superior esquerdo -> TexCoord 0,0
        -1.0f, -1.0f, 0.0f, 1.0f,  // Inferior esquerdo -> TexCoord 0,1
         1.0f, -1.0f, 1.0f, 1.0f,  // Inferior direito -> TexCoord 1,1
        -1.0f,  1.0f, 0.0f, 0.0f,  // Superior esquerdo -> TexCoord 0,0
         1.0f, -1.0f, 1.0f, 1.0f,  // Inferior direito -> TexCoord 1,1
         1.0f,  1.0f, 1.0f, 0.0f   // Superior direito -> TexCoord 1,0
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // criar textura
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cenario.n_col, cenario.n_lin, 0, GL_RGB, GL_UNSIGNED_BYTE, cenario.canvas.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // manter janela aberta até o usuário fechá-la
    while (!glfwWindowShouldClose(window)) {
        // processar entrada
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // renderizar
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // limpar
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    glfwTerminate();


    // Liberar memória
    // delete esfera;
    delete plano_frontal;
    delete plano_chao;
    delete plano_direita;
    delete plano_esquerda;
    delete plano_teto;
    // delete cilindro;
    // delete cone;
    delete malha;
    delete camera; // quando não usar, apagar daqui
   
    return 0;
}