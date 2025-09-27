# Tarefa 02: Iluminar a esfera

## Descrição
Modificar o método da Tarefa 01 para que, caso haja interseção de um raio com a esfera, a cor retornada seja dada pela energia luminosa que vem do ponto de interseção PI em direção ao olho do observador.  Essa energia luminosa é o resultado da interação entre a energia luminosa emitida pela fonte pontual e o material da esfera no ponto de interseção. 
Ela é composta de duas parcelas: a reflexão DIFUSA (I_d) e a reflexão Especular. (I_e), onde

I_d =( I_F@K)* (l . n)

I_e = (I_F@K)*(v . r)^m.

Use os seguintes atributos da fonte de luz pontual:

I_F = (0.7, 0.7, 0.7)  // Intensidade da fonte pontual

P_F = (0, 5, 0)   // Posição da fonte pontual situada a 5 metros acima do olho do observador.

## Passo a Passo para Implementar

A partir do ponto em que finalizamos o código anterior, vamos começar a dar o aspecto 3D à esfera, utilizando iluminação.

Ao final da tarefa 1 tínhamos: 

```
if (delta >= 0) {
                pixel[0] = cor_intersecao[0];
                pixel[1] = cor_intersecao[1];
                pixel[2] = cor_intersecao[2];
```
Neste ponto, quando o t (delta) fosse maior que zero, nós pintavamos o pixel em específico com a cor vermelha. O "pixel em específico" é o ponto em que estamos dentro das iterações de linhas e colunas que já sabemos como ocorrem. A ideia é utilizar a maioria das fórmulas da aula do dia 25/09 no interior desse if.

Como?

1. Vamos começar declarando as constantes I_F e P_F, que serão vetores de três posições. Isso fora do if, claro.

2. Agora, já dentro do if, vamos achar o ponto de interseção a partir do t encontrado, usando: **P(t) = P0 + t * dr**. Aqui é importante perceber que na tarefa passada essa fórmula era diluída no momento em que gerávamos a equação do segundo grau, pra achar aqueles valores a, b e c. Só que agora precisamos do exato valor da interseção pra alguns calculos posteriores (será o fator PI a partir das próximas etapas).

3. Vamos encontrar os vetores n, l e v agora. Temos fórmulas pra isso, é de boa.
    - **n = (PI - C) / ||PI - C||**
    - **l = (P_F - PI) / ||P_F - PI||**
    - **v = -direção**

    OBS: PI é o valor da interseção que achamos na etapa passada, P_F é a posição da fonte de luz que o professor deu na descrição da tarefa e C (centro da esfera) e direção (dr) são valores que já temos.

4. Agora precisamos achar o vetor r, que tem fórmula dada:
    - **r = 2 * (n . l) * n - l**.

5. E aí pra que serve isso? Pra usar nas formulas da iluminação que estão na descrição da tarefa.

    - **I_d =( I_F@K) * (l . n)**
    - **I_e = (I_F@K) * (v . r)^m.**  

    OBS.1: O "@" é o produto componente a componente, imagine assim: temos dois vetores de três posições a e b e queremos a@b, isso vai gerar um novo vetor c, onde: 
    c[3] = [a[0] * b[0], a[1] * b[1], a[2] * b[2]]

    OBS.2: A gente não tem nem K e nem m dados na tarefa, precisamos supor valores pra isso. Aí aqui, quanto ao K, tem um detalhe: K é um vetor com as propiedades de reflexão do matérial (EU ACHO) que tem três componentes pra representar o rgb, isso está nas fotos da aula do dia 25/09. Nessas mesmas fotos vemos que não temos só um K e sim dois: K_dif e K_esp que são diferentes, aqui temos que ver se podemos assumir um mesmo valor pra eles e também ver qual seria esse valor, a declaração do K seria junto às constantes da etapa 1. Já quanto ao m, é um valor que vai dizer quando a superfície brilha, temos que ver um valor legal pra isso também.

6. Uma vez resolvidas as observações da etapa passada e os vetores I_d e I_e calculados, podemos achar a "cor final iluminada" gerando FINALMENTE, o vetor IE:
    - **IE = I_d + I_e**

7. E aí sim, no final do if, ao invés de pintar o pixel com a cor vermelha, pintamos com a cor IE que acabamos de achar.





