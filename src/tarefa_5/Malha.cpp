#include "../include/Malha.h"
#include <cfloat>
#include <cmath>

Malha::Malha(vector<Vertice>& vertices, vector<Aresta>& arestas, vector<Face>& faces, Cor& ke, Cor& kd, Cor& ka, float m)
    : ObjetoAbstrato(ke, kd, ka, m), vertices(vertices), arestas(arestas), faces(faces) {}

Malha::Malha() {}

void Malha::adicionarVertice(Vertice& v) {
    vertices.push_back(v);
}

void Malha::adicionarAresta(Aresta& a) {
    arestas.push_back(a);
}

void Malha::adicionarFace(Face& f) {
    faces.push_back(f);
}

bool Malha::intersecao(Raio& raio, float& t) {
    bool temIntersecao = false;
    float tEscolhido = FLT_MAX;
    
    for (int i = 0; i < (int)faces.size(); i++) {
        Face& face = faces[i];
        
        int idAresta1 = face.idAresta1;
        int idAresta2 = face.idAresta2;
        int idAresta3 = face.idAresta3;

        int idV1 = arestas[idAresta1].idVertice1;
        int idV2 = arestas[idAresta1].idVertice2;
        int idV3 = -1;
        
        // o terceiro vertice é aquele que não está na aresta1
        int v21 = arestas[idAresta2].idVertice1;
        int v22 = arestas[idAresta2].idVertice2;
        
        if (v21 != idV1 && v21 != idV2) {
            idV3 = v21;
        } else if (v22 != idV1 && v22 != idV2) {
            idV3 = v22;
        }
        
        // se não encontrou na aresta2, procura na aresta3
        if (idV3 == -1) {
            int v31 = arestas[idAresta3].idVertice1;
            int v32 = arestas[idAresta3].idVertice2;
            
            if (v31 != idV1 && v31 != idV2) {
                idV3 = v31;
            } else if (v32 != idV1 && v32 != idV2) {
                idV3 = v32;
            }
        }
        
        // o pdf ensina desse jeito abaixo, mas algumas faces ficam incorretas, então mudei para o jeito acima
        // int idAresta1 = face.idAresta1;
        // int idAresta2 = face.idAresta2;

        // int idVertice11 = arestas[idAresta1].idVertice1;
        // int idVertice12 = arestas[idAresta1].idVertice2;

        // int idVertice21 = arestas[idAresta2].idVertice1;
        // int idVertice22 = arestas[idAresta2].idVertice2;

        // float v1, v2, v3;

        // float n1 = ((float)idVertice11 * (float)idVertice12);
        // float n = n1/(float)idVertice21;

        // if (n == ((float)idVertice11) || n == ((float)idVertice12)) {
        //     v1 = (float)idVertice21;
        //     v2 = (float)idVertice22;
        //     v3 = n;
        // } else {
        //     v1 = idVertice22;
        //     v2 = idVertice21;
        //     v3 = n1/v1;
        // }

        Ponto p1 = vertices[idV1].v;
        Ponto p2 = vertices[idV2].v;
        Ponto p3 = vertices[idV3].v;

        Vetor r1 = p2.subPonto(p1);
        Vetor r2 = p3.subPonto(p1);

        Vetor normal = r1.produtoVetorial(r2).normalizado();
        
        Vetor dr = raio.direcao;
        Vetor w = raio.origem.subPonto(p1);

        float drdotn = dr.produtoEscalar(normal);
        float tLocal = -(w.produtoEscalar(normal)/drdotn);

        if (drdotn != 0 && tLocal > 0) {
            Ponto Pi = raio.equacaoRaio(tLocal);

            Vetor s1 = p1.subPonto(Pi);
            Vetor s2 = p2.subPonto(Pi);
            Vetor s3 = p3.subPonto(Pi);

            Vetor s3xs1 = s3.produtoVetorial(s1);
            Vetor s1xs2 = s1.produtoVetorial(s2);

            float c1 = normal.produtoEscalar(s3xs1)/r1.produtoVetorial(r2).norma();
            float c2 = normal.produtoEscalar(s1xs2)/r1.produtoVetorial(r2).norma();
            float c3 = 1 - c1 - c2;

            // Vetor v = Pi.subPonto(p1);

            // Vetor vxr2 = v.produtoVetorial(r2);
            // Vetor r1xr2 = r1.produtoVetorial(r2);
            // float c1 = (normal.produtoEscalar(vxr2))/normal.produtoEscalar(r1xr2);

            // Vetor r1xv = r1.produtoVetorial(v);
            // float c2 = (normal.produtoEscalar(r1xv))/normal.produtoEscalar(r1xr2);

            // float c3 = 1 - c1 - c2;

            if (c1 >= 0 && c2 >= 0 && c3 >= 0) {
                if (!temIntersecao || tLocal < tEscolhido) {
                    temIntersecao = true;
                    tEscolhido = tLocal;
                    t = tEscolhido;
                    normalIntersecao = normal;
                }
            }
        }
    }
    
    return temIntersecao;
}

Cor Malha::calcularIluminacao(Ponto& Pi, Vetor& direcao_raio, FonteIluminacao& fonte) {
    Vetor normal = normalIntersecao;

    // teste que o monitor ensinou
    if (normal.produtoEscalar(direcao_raio) > 0) {
        normal = normal.vetorNegativo();
    }

    // Vetor da luz e do observador
    Vetor l = fonte.P_F.subPonto(Pi).normalizado();
    Vetor v = direcao_raio.vetorNegativo();

    float produto_nl = max(0.0f, normal.produtoEscalar(l));
    Vetor r = normal.multiEscalar(2.0f * produto_nl).subVetor(l).normalizado();

    Cor IFKd = fonte.I_F.multiComponente(Kd);
    Cor IFKe = fonte.I_F.multiComponente(Ke);

    Cor I_d = IFKd.multiEscalar(produto_nl);
    float produto_vr = max(0.0f, v.produtoEscalar(r));
    Cor I_e = IFKe.multiEscalar(pow(produto_vr, m));

    Cor I_a = fonte.I_A.multiComponente(Ka);

    Cor IE = I_d.somarCor(I_e).somarCor(I_a);
    IE.limitar();

    return IE;
}