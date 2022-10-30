#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definindo algumas informações globais
// Defining some global information
#define linhas 8
#define colunas 8
#define horsePossibleMoviments 8

typedef struct positionObject {
    int x;
    int y;
} positionObject;

// Variável global que guarda as posíveis movimentações do cavalo.
// Global variable that stores the possible movements of the horse.
positionObject horseMoviments[] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, -1}, {-2, 1}};

// Inicialização das funções utilizadas;
// Initialization of the functions;
int check_valid_movement(int x, int y);
int check_possible_movement(int x, int y, int tour[linhas][colunas]);
int getValidNeighbours(positionObject neighbour_array[], int x, int y, int board[linhas][colunas]);
void mark_step(int x, int y, int position_counter, int board[linhas][colunas]);
void printMatrix(int matriz[8][8], int num_iteracoes, int num_retrocessos);
void warnsdorff_heuristic(positionObject neighbours[], int neighbour_amount);
int simplifyCoordenates(const void* a, const void* b);
int passeio(int x, int y, int moves, long int*iterations, long int* regressions, int board[linhas][colunas]);

// Verifica se o par ordenado passado por parâmetro está dentro do tabuleiro
// Checks if the ordered pair passed by parameter is inside the board
int check_valid_movement(int x, int y){
    return (x >= 0 && y >= 0 && x < linhas && y < colunas) ? 1 : 0;
}

// Verifica se o cavalo pode saltar para o par ordenado passado por parâmetro verificando se esse par é válido e se ele ainda não foi visitado
// Checks if the horse can jump to the ordered pair passed by parameter checking if this pair is valid and if it has not yet been visited
int check_possible_movement(int x, int y, int board[linhas][colunas]){
    int is_in_bounds = check_valid_movement(x, y);
    
    if(is_in_bounds) {
        if(!board[x][y] != 0) {
            return 1;
        }
    }

    return 0;
}

// Verifica a quantidade de movimentos válidos que o cavalo pode fazer a partir de uma posição (x, y) 
// no tabuleiro e atribui esses movimentos válidos para um array de pares ordenados passado por parâmetro
// Checks the amount of valid moves the knight can make from a position (x, y) on the board and assigns these 
// valid moves to an array of ordered pairs passed by parameter
int getValidNeighbours(positionObject neighbour_array[], int x, int y, int board[linhas][colunas]) {
    int counter = 0;
    int k = 0;
    while(k < horsePossibleMoviments){
        if(check_possible_movement((x + horseMoviments[k].x), (y + horseMoviments[k].y), board)){
            positionObject c;
            c.x = x + horseMoviments[k].x;
            c.y = y + horseMoviments[k].y;
            neighbour_array[counter] = c;
            counter++;
        }
        k++;
    }

    return counter;
}

// Adiciona à casa de coordenadas x e y o número do pulo do cavalo até o momento
// Adds to the position of coordinates x and y the number of the horse's jump so far
void mark_step(int x, int y, int moves, int board[linhas][colunas]){
    board[x][y] = moves;
}

// Cria um arquivo chamado "saida.txt" que contém a matriz de resultados do passeio do cavalo
// Creates a file named "saida.txt" that contains the result matrix of the knight'stour
void printMatrix(int matriz[8][8], int num_iteracoes, int num_retrocessos) {
    FILE *arq;
    arq = fopen("saida.txt", "wt");

    if(arq != NULL) {
        for(int i = 0; i < linhas; ++i) {
            for(int j = 0; j < colunas; ++j) {
                if(matriz[i][j] < 10){
                    fprintf(arq, "0%d ", matriz[i][j]);
                } else {
                    fprintf(arq, "%d ", matriz[i][j]);
                }
                if(j == 7){
                    fprintf(arq, "\n");
                }
            }
        }
            
        fprintf(arq, "%ld ", num_iteracoes);
        fprintf(arq, "%ld", num_retrocessos);

        fclose(arq);
    } else {
        printf("Falha ao criar arquivo de texto.\n");
    }
}

// Regra de Warsndorff - Heuristica que nos permite reduzir o número de iterações pela ordenação dos movimentos 
// baseada na maior distaâcia euclidiana de seus pontos até a posição central do tabuleiro, isso utilizando a técnica Quick Sort.
// Warsndorff's Rule - Heuristic that allows us to reduce the number of iterations by ordering the moves
// based on the longest Euclidean distance from your points to the center position of the board, using the Quick Sort technique.
void warnsdorff_heuristic(positionObject neighbours[], int neighbour_amount) {
    qsort(neighbours, neighbour_amount, sizeof(positionObject), simplifyCoordenates);
}

// Função que retorna a diferença da distância distancia euclidiana de duas coordenadas até o centro do tabuleiro
// Function that returns the difference of the Euclidean distance of two coordinates to the center of the board
int simplifyCoordenates(const void* a, const void* b) {
    positionObject* curr = (positionObject *)a;
    positionObject* next = (positionObject *)b;

    double board_center = (double)((linhas - 1)) / 2;
    double currentNorm = pow(curr->x - board_center, 2) + pow(curr->y - board_center, 2);
    double secondNorm = pow(next->x - board_center, 2) + pow(next->y - board_center, 2);

    return secondNorm - currentNorm;
}

// Faz o passeio do cavalo
// Makes the horse tour
int passeio(int x, int y, int moves, long int*iterations, long int* regressions, int board[linhas][colunas]) {
    mark_step(x, y, moves, board);
    *(iterations) = *(iterations) + 1;

    if(moves == 64) return 1;

    //definir proximos movimentos válidos
    positionObject neighbour_array[8];
    int close_neighbours_amount = getValidNeighbours(neighbour_array, x, y, board);
    warnsdorff_heuristic(neighbour_array, close_neighbours_amount);

    for(int i = 0; i < close_neighbours_amount; i++) {
        if(passeio(neighbour_array[i].x, neighbour_array[i].y, moves + 1, iterations, regressions, board)) return 1;
        *(regressions) = *(regressions) + 1;
    }

    mark_step(x, y, 0, board);
    return 0;
}