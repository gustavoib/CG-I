#include "../trabalho_final/include/Matriz.h"
#include <cmath>

#define M_PI 3.14159265358979323846

Matriz::Matriz() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = 0.0f;
        }
    }
}

Matriz::Matriz(float valores[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = valores[i][j];
        }
    }
}

Matriz Matriz::identidade() {
    float id[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(id);
}

Matriz Matriz::inversa(const Matriz& matriz) {
    Matriz inv;

    float s0 = matriz.m[0][0] * matriz.m[1][1] - matriz.m[1][0] * matriz.m[0][1];
    float s1 = matriz.m[0][0] * matriz.m[1][2] - matriz.m[1][0] * matriz.m[0][2];
    float s2 = matriz.m[0][0] * matriz.m[1][3] - matriz.m[1][0] * matriz.m[0][3];
    float s3 = matriz.m[0][1] * matriz.m[1][2] - matriz.m[1][1] * matriz.m[0][2];
    float s4 = matriz.m[0][1] * matriz.m[1][3] - matriz.m[1][1] * matriz.m[0][3];
    float s5 = matriz.m[0][2] * matriz.m[1][3] - matriz.m[1][2] * matriz.m[0][3];

    float c5 = matriz.m[2][2] * matriz.m[3][3] - matriz.m[3][2] * matriz.m[2][3];
    float c4 = matriz.m[2][1] * matriz.m[3][3] - matriz.m[3][1] * matriz.m[2][3];
    float c3 = matriz.m[2][1] * matriz.m[3][2] - matriz.m[3][1] * matriz.m[2][2];
    float c2 = matriz.m[2][0] * matriz.m[3][3] - matriz.m[3][0] * matriz.m[2][3];
    float c1 = matriz.m[2][0] * matriz.m[3][2] - matriz.m[3][0] * matriz.m[2][2];
    float c0 = matriz.m[2][0] * matriz.m[3][1] - matriz.m[3][0] * matriz.m[2][1];

    float det =
          s0 * c5 - s1 * c4 + s2 * c3
        + s3 * c2 - s4 * c1 + s5 * c0;

    if (fabs(det) < 1e-6f) {
        return Matriz::identidade();
    }

    float invDet = 1.0f / det;

    inv.m[0][0] = ( matriz.m[1][1] * c5 - matriz.m[1][2] * c4 + matriz.m[1][3] * c3) * invDet;
    inv.m[0][1] = (-matriz.m[0][1] * c5 + matriz.m[0][2] * c4 - matriz.m[0][3] * c3) * invDet;
    inv.m[0][2] = ( matriz.m[3][1] * s5 - matriz.m[3][2] * s4 + matriz.m[3][3] * s3) * invDet;
    inv.m[0][3] = (-matriz.m[2][1] * s5 + matriz.m[2][2] * s4 - matriz.m[2][3] * s3) * invDet;

    inv.m[1][0] = (-matriz.m[1][0] * c5 + matriz.m[1][2] * c2 - matriz.m[1][3] * c1) * invDet;
    inv.m[1][1] = ( matriz.m[0][0] * c5 - matriz.m[0][2] * c2 + matriz.m[0][3] * c1) * invDet;
    inv.m[1][2] = (-matriz.m[3][0] * s5 + matriz.m[3][2] * s2 - matriz.m[3][3] * s1) * invDet;
    inv.m[1][3] = ( matriz.m[2][0] * s5 - matriz.m[2][2] * s2 + matriz.m[2][3] * s1) * invDet;

    inv.m[2][0] = ( matriz.m[1][0] * c4 - matriz.m[1][1] * c2 + matriz.m[1][3] * c0) * invDet;
    inv.m[2][1] = (-matriz.m[0][0] * c4 + matriz.m[0][1] * c2 - matriz.m[0][3] * c0) * invDet;
    inv.m[2][2] = ( matriz.m[3][0] * s4 - matriz.m[3][1] * s2 + matriz.m[3][3] * s0) * invDet;
    inv.m[2][3] = (-matriz.m[2][0] * s4 + matriz.m[2][1] * s2 - matriz.m[2][3] * s0) * invDet;

    inv.m[3][0] = (-matriz.m[1][0] * c3 + matriz.m[1][1] * c1 - matriz.m[1][2] * c0) * invDet;
    inv.m[3][1] = ( matriz.m[0][0] * c3 - matriz.m[0][1] * c1 + matriz.m[0][2] * c0) * invDet;
    inv.m[3][2] = (-matriz.m[3][0] * s3 + matriz.m[3][1] * s1 - matriz.m[3][2] * s0) * invDet;
    inv.m[3][3] = ( matriz.m[2][0] * s3 - matriz.m[2][1] * s1 + matriz.m[2][2] * s0) * invDet;

    return inv;
}

Matriz Matriz::transposta(const Matriz& matriz) {
    Matriz transposta;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            transposta.m[i][j] = matriz.m[j][i];
        }
    }
    return transposta;
}

Matriz Matriz::rotacaoX(float angulo) {
    float rad = angulo * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    float rot[4][4] = {
        {1, 0, 0, 0},
        {0, c, -s, 0},
        {0, s, c, 0},
        {0, 0, 0, 1}
    };
    return Matriz(rot);
}

Matriz Matriz::rotacaoY(float angulo) {
    float rad = angulo * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    float rot[4][4] = {
        {c, 0, s, 0},
        {0, 1, 0, 0},
        {-s, 0, c, 0},
        {0, 0, 0, 1}
    };
    return Matriz(rot);
}

Matriz Matriz::rotacaoZ(float angulo) {
    float rad = angulo * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    float rot[4][4] = {
        {c, -s, 0, 0},
        {s, c, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(rot);
}

// Matriz Matriz::rotacaoArbitraria(Vetor eixo, float angulo) {
//     Vetor n = eixo.normalizado();
//     float rad = angulo * M_PI / 180.0f;
//     float c = cos(rad);
//     float s = sin(rad);
//     float rot[4][4] = {
//         {c + n.x*n.x*(1-c), n.x*n.y*(1-c) - n.z*s, n.x*n.z*(1-c) + n.y*s, 0},
//         {n.y*n.x*(1-c) + n.z*s, c + n.y*n.y*(1-c), n.y*n.z*(1-c) - n.x*s, 0},
//         {n.z*n.x*(1-c) - n.y*s, n.z*n.y*(1-c) + n.x*s, c + n.z*n.z*(1-c), 0},
//         {0, 0, 0, 1}
//     };
//     return Matriz(rot);
// }

Matriz Matriz::rotacaoArbitraria(Vetor eixo, float angulo) {
    // normalizar o eixo
    Vetor k = eixo.normalizado();
    
    // olha se não é paralelo
    Vetor temp = Vetor(1, 0, 0);
    if (fabs(k.x) > 0.9f) {
        temp = Vetor(0, 1, 0);
    }
    
    // x local perpendicular ao eixo
    Vetor i = k.produtoVetorial(temp);
    i = i.normalizado();
    
    // y local perpendicular a ambos
    Vetor j = k.produtoVetorial(i);
    j = j.normalizado();
    
    // matriz que transforma mundo → sistema local
    float M_data[4][4] = {
        {i.x, i.y, i.z, 0},
        {j.x, j.y, j.z, 0},
        {k.x, k.y, k.z, 0},
        {0, 0, 0, 1}
    };
    Matriz M(M_data);
    
    // para voltar ao mundo
    Matriz M_linha = Matriz::transposta(M);
    
    // rotação simples em Z (sistema local)
    Matriz R_z = Matriz::rotacaoZ(angulo);
    
    // transformação completa
    Matriz resultado = M_linha.multiplicar(R_z).multiplicar(M);
    
    return resultado;
}


Matriz Matriz::translacao(float tx, float ty, float tz) {
    float trans[4][4] = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}
    };
    return Matriz(trans);
}

Matriz Matriz::escala(float sx, float sy, float sz) {
    float esc[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    return Matriz(esc);
}

Matriz Matriz::espelhamentoXY() {
    float esp[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, -1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(esp);
}

Matriz Matriz::espelhamentoXZ() {
    float esp[4][4] = {
        {1, 0, 0, 0},
        {0, -1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(esp);
}

Matriz Matriz::espelhamentoYZ() {
    float esp[4][4] = {
        {-1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(esp);
}

Matriz Matriz::cisalhamentoYX(float angulo) {
    float a = tan(angulo * M_PI / 180.0f);
    float cis[4][4] = {
        {1, a, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(cis);
}

Matriz Matriz::cisalhamentoXY(float angulo) {
    float a = tan(angulo * M_PI / 180.0f);
    float cis[4][4] = {
        {1, 0, 0, 0},
        {a, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(cis);
}

Matriz Matriz::cisalhamentoYZ(float angulo) {
    float a = tan(angulo * M_PI / 180.0f);
    float cis[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, a, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(cis);
}

Matriz Matriz::cisalhamentoZY(float angulo) {
    float a = tan(angulo * M_PI / 180.0f);
    float cis[4][4] = {
        {1, 0, 0, 0},
        {0, 1, a, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(cis);
}

Matriz Matriz::cisalhamentoXZ(float angulo) {
    float a = tan(angulo * M_PI / 180.0f);
    float cis[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {a, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(cis);
}

Matriz Matriz::cisalhamentoZX(float angulo) {
    float a = tan(angulo * M_PI / 180.0f);
    float cis[4][4] = {
        {1, 0, a, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    return Matriz(cis);
}

Matriz Matriz::multiplicar(const Matriz& outra) const {
    Matriz resultado;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            resultado.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                resultado.m[i][j] += m[i][k] * outra.m[k][j];
            }
        }
    }
    return resultado;
}

Vetor Matriz::multiplicarVetor(const Vetor& v) const {
    float x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z;
    float y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z;
    float z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z;
    return Vetor(x, y, z);
}

Ponto Matriz::multiplicarPonto(const Ponto& p) const {
    float x = m[0][0]*p.x + m[0][1]*p.y + m[0][2]*p.z + m[0][3];
    float y = m[1][0]*p.x + m[1][1]*p.y + m[1][2]*p.z + m[1][3];
    float z = m[2][0]*p.x + m[2][1]*p.y + m[2][2]*p.z + m[2][3];
    float w = m[3][0]*p.x + m[3][1]*p.y + m[3][2]*p.z + m[3][3];
    if (w != 1.0f) {
        x /= w;
        y /= w;
        z /= w;
    }
    return Ponto(x, y, z);
}