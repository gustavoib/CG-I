Escreva um código, baseado na discussão das duas primeiras aulas, que pinte uma esfera no canvas. Os requisitos são os seguintes:
1) Defina uma janela através da qual o pintor verá a esfera 
- A largura da janela, em metros, será armazenada na variável wJanela
- A altura. da janela, em metros, será armazenada na variável  hJanela
- O centro da janela está sobre o eixo z do sistema de coordenadas na posição (0, 0, - dJanela) em metros. Assim, todos os pontos no plano da Janela terão coordenada z = - dJanela.

2) O olho do pintor está na origem do sistema de coordenadas (0,0,0)


3) O raio da esfera deve ser armazenado na variável rEsfera

4) O centro da esfera deve estar sobre o eixo z com coordenada z < - (dJanela + rEsfera)

5) A cor da esfera deve ser esfColor = 255, 0, 0


6)  A cor de background deve ser cinza bgColor = 100, 100, 100

7) Defina o número de colunas nCol e o número de linhas nLin da matriz de cores da imagem.
- nCol representa tanto o número de colunas na tela de mosquito que está presa na Janela, quanto o número de colunas do quadriculado que o pintor marcou a lápis no Canvas de pintura.
- nLin, de maneira análoga, representa tanto o número de linhas na tela de mosquito que está presa na Janela, quanto o número de linhas do quadriculado que o pintor marcou a lápis no Canvas de pintura

Note que
O loop aninhado mais externo é o loop de linhas que vai de 0 até nLin - 1.  ( for int l = 0; l < nLin; l++)
O loop aninhado mais interno é o loop de colunas que vai de 0 até nCol -1  (for int c =0; c < nCol; c++)

As dimensões dos retângulos da tela de mosquito são:
Dx = wJanela/nCol
Dy = hJanela/nLin

As coordenadas do ponto do centro de um retângulo da tela de mosquito correspondente ao retângulo (riscado a lápis) na posição (l, c) é dado por

x = - wJanela/2. + Dx/2  + c*Dx
y =.  hJanela/2.  -  Dy/2  -  l*Dy

Cada raio (semi reta) parte do olho do pintor E = (0,0, 0) e  passa pelo ponto (x, y, -dJanela).

Caso o raio enviado não tenha interseção com a esfera, armazene a cor de background na posição (l, c) da matriz de cores do Canvas.
Caso o raio tangencie ou tenha interseção plena com a esfera, armazene a cor da esfera (esfColor) na posição (l, c) da matriz de cores do Canvas.