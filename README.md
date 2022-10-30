# knightsTour
Código desenvolvido para um trabalho da faculdade cujo intuito era construir um código para resolver o problema do passeio do cavalo a partir de qualquer casa de um tabuleiro de xadrez 8x8. 

Para executar o código, basta compilar os arquivos e executar o arquivo main.
O resultado do processo será gravado em um arquivo de texto criado pelo próprio programa se um resultado for encontrado.

- Nas 8 primeiras linhas desse arquivo de texto (8 pois é o número default de linhas que um tabuleiro de xadrez possui, mas esse número pode ser alterado fazendo poucas mudanças no código, ou seja, o algorítmo também funciona para tabuleiros quadrados maiores e menores, por exemplo 10x10) estarão presentes as coordenadas do tabuleiro 8x8 com seus respectivos índices de acesso pelo cavalo (ex: 23 -> quer dizer que essa casa foi a vigésima terceira acessada pelo cavalo) e na última linha estará presente em sequência e respectivamente o número de iterações necessárias para o algorítmo achar o resultado e o número de retrocessos;