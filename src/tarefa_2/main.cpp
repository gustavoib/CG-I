#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

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
const int n_col = 400;
const int n_lin = 400;

// iluminação
float I_F[3] = {0.7f, 0.7f, 0.7f};
float P_F[3] = {0.0f, 5.0f, 0.0f};
float K[3] = {1.0f, 0.0f, 0.0f};

// buffer de cores (canvas)
std::vector<unsigned char> canvas(n_col * n_lin * 3);

float produto_escalar(const float a[3], const float b[3]) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void equacao_raio(const float p0[3], float t, const float direcao[3], float pt[3]) {
    for (int i = 0; i < 3; ++i) {
        pt[i] = p0[i] + t * direcao[i];
    }
}

float norma(const float v[3]) {
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

void multi_componente(const float a[3], const float b[3], float resultado[3]) {
    for (int i = 0; i < 3; ++i) {
        resultado[i] = a[i] * b[i];
    }
}

// funcao para lançar os raios
void render() {
    float delta_x = w_janela / n_col;
    float delta_y = h_janela / n_lin;

    float z = -d_janela;
    for (int lin = 0; lin < n_lin; lin++) {
        float y =  h_janela/2.0f - delta_y/2.0f - lin*delta_y;
        for (int col = 0; col < n_col; col++) {
            float x = -w_janela/2.0f + delta_x/2.0f + col*delta_x;

            unsigned char* pixel = &canvas[(lin*n_col + col) * 3];
            
            float direcao[3] = {
                x - olho[0], 
                y - olho[1], 
                z - olho[2], 
            };

            float direcao_normal = sqrt((direcao[0]*direcao[0]) + (direcao[1]*direcao[1]) + (direcao[2]*direcao[2]));
            
            float d[3] = {
                direcao[0]/direcao_normal, 
                direcao[1]/direcao_normal, 
                direcao[2]/direcao_normal, 
            };

            float w[3] = {
                olho[0] - centro_esfera[0], 
                olho[1] - centro_esfera[1], 
                olho[2] - centro_esfera[2], 
            };
    
            float a = produto_escalar(d, d);
            float b = 2.0f * produto_escalar(w, d);
            float c = produto_escalar(w, w) - raio_esfera*raio_esfera;

            float delta = b*b - 4*a*c;

            if (delta >= 0) {
                float t;
                
                float t1 = (-b - sqrt(delta)) / (2.0f * a);
                float t2 = (-b + sqrt(delta)) / (2.0f * a);
                    
                t = min(t1, t2);
        

                float Pi[3];
                equacao_raio(olho, t, d, Pi);

                float Pi_minus_c[3] = {
                    Pi[0] - centro_esfera[0], 
                    Pi[1] - centro_esfera[1], 
                    Pi[2] - centro_esfera[2]};

                float norma_pic = norma(Pi_minus_c);
                float n[3] = {
                    ((Pi_minus_c[0])/norma_pic), 
                    ((Pi_minus_c[1])/norma_pic), 
                    ((Pi_minus_c[2])/norma_pic)
                };

                float P_F_minus_Pi[3] = {
                    P_F[0] - Pi[0],
                    P_F[1] - Pi[1],
                    P_F[2] - Pi[2]
                };

                float norma_pfpi = norma(P_F_minus_Pi);
                float l[3] = {
                    ((P_F_minus_Pi[0])/norma_pfpi), 
                    ((P_F_minus_Pi[1])/norma_pfpi), 
                    ((P_F_minus_Pi[2])/norma_pfpi)
                };

                float v[3] = {
                    -d[0],
                    -d[1],
                    -d[2]
                };

                float produto_nl = produto_escalar(n, l);

                float r[3] = {
                    2.0f * produto_nl*n[0] - l[0],
                    2.0f * produto_nl*n[1] - l[1],
                    2.0f * produto_nl*n[2] - l[2]
                };

                float IFK[3];
                multi_componente(I_F, K, IFK);

                float produto_nl_limitado = max(0.0f, produto_escalar(n, l));

                float I_d[3] = {
                    IFK[0] * produto_nl_limitado,
                    IFK[1] * produto_nl_limitado, 
                    IFK[2] * produto_nl_limitado
                };

                float m = 10.0f;
                float produto_vr_limitado = max(0.0f, produto_escalar(v, r));
                float vrm = pow(produto_vr_limitado, m);

                float I_e[3] = {
                    IFK[0] * vrm,
                    IFK[1] * vrm,
                    IFK[2] * vrm
                };

                float IE[3] = {
                    I_d[0] + I_e[0],
                    I_d[1] + I_e[1],
                    I_d[2] + I_e[2]
                };

                IE[0] = min(1.0f, max(0.0f, IE[0]));
                IE[1] = min(1.0f, max(0.0f, IE[1]));
                IE[2] = min(1.0f, max(0.0f, IE[2]));

                pixel[0] = IE[0]*255.0f;
                pixel[1] = IE[1]*255.0f;
                pixel[2] = IE[2]*255.0f;
            } else {
                pixel[0] = cor_background[0];
                pixel[1] = cor_background[1];
                pixel[2] = cor_background[2];
            }
        }
    }
}
 
void salvarPPM(const std::string& nome_arquivo, int largura, int altura, const std::vector<unsigned char>& buffer) {
    std::ofstream arquivo(nome_arquivo, std::ios::binary);
    
    if (!arquivo) {
        std::cerr << "Erro ao abrir arquivo " << nome_arquivo << " para escrita.\n";
        return;
    }

    arquivo << "P6\n" << largura << " " << altura << "\n255\n";

    arquivo.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

    arquivo.close();
}

int main() {

    render();

    salvarPPM("tarefa_2.ppm", n_col, n_lin, canvas);

    return 0;
}