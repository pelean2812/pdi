# pdi
Repositório destinado a disciplina DCA0445 - Processamento Digital de Imagens
## Unidade 1
Nesta seção será apresentada as resoluções de alguns dos exericícios práticos.

### Exercício 1
> Enunciado da questão:  Utilizando o programa da Listagem 4 como referência, implemente um programa regions.cpp. Esse programa deverá solicitar ao usuário as coordenadas de dois pontos P1 e P2 localizados dentro dos limites do tamanho da imagem e exibir que lhe for fornecida. Entretanto, a região definida pelo retângulo de vértices opostos definidos pelos pontos P1 e P2
 será exibida com o negativo da imagem na região correspondente. O efeito é ilustrado na Figura 4.

 Em suma, dada uma imagem, o usuário deve digitar as coordendas de dois pontos, e estes serão utilizados para delimitar um retângulo. Tudo o que estiver dentro do retângulo da imagem será aplicado o efeito de negativo nas cores. Bem como mostra a imagem abaixo, na qual o primeiro ponto tem coordenadas ```(100,100)``` e o segundo ponto tem coordenadas ```(500,500)```, ou seja, a imagem ficara negativa dentro do retângulo de vértices ```(100,100)```, ```(100,500)```, ```(500,100)``` e ```(500,500)```:

 ![luffy](./imgExercicios/exercicio2_1.PNG)

O código desenvolvido para a resolução deste exercício pode ser visto [aqui](./pdiTrabalhoU1/exercicio2.1/exercicio.cpp), e as imagens geradas estão [nesta pasta](./pdiTrabalhoU1/exercicio2.1/) (são as imagens "luffy", que é a imagem original e a imagem "luffyNegative", que é a imagem com o efeito negativo).
 

