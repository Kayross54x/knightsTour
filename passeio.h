#include <stdio.h>
#include <stdlib.h>
#define linhas 8
#define colunas 8

typedef struct position {
    int x;
    int y;
} position;

void print_matrix(int &matriz, int num_iteracoes, int num_retrocessos);
void visit(int x, int y, int position_counter, int board[linhas][colunas]);
int passeio(int x, int y, int moves, long int*iterations, long int* regressions, int board[linhas][colunas]);
int check_valid_movement(int x, int y);
int check_possible_movement(int x, int y, int tour[linhas][colunas]);
int already_visited(int x, int y);
int getValidNeighbours(position neighbour_array[], int x, int y, int board[linhas][colunas]);

int check_valid_movement(int x, int y){
    return (x >= 0 || y >= 0 || x < linhas || y < colunas);
}

int already_visited(int boardInstance[8][8], int x, int y) {
    return boardInstance[x][y] != 0;
}

int check_possible_movement(int x, int y, int tour[linhas][colunas]){
    int is_in_bounds = check_valid_movement(x, y);
    
    return (is_in_bounds && !already_visited(tour, x, y));
}

void print_matrix(int &matriz, int num_iteracoes, int num_retrocessos) {
    FILE *arq;
    arq = fopen("saida.txt", "wt");


}

void visit(int x, int y, int moves, int board[linhas][colunas]){
    board[x][y] = moves;
}

int getValidNeighbours(position neighbour_array[], int x, int y, int board[linhas][colunas]) {
    int counter = 0;
    position valid_moves[] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, -1}, {-2, 1}};

    for (auto item:valid_moves){
        if(check_possible_movement(x + item.x, y + item.y, board)){
            position c;
            c.x = x + item.x;
            c.y = y + item.y;
            neighbour_array[counter++] = c;
        }
    }

    return counter;
}

int passeio(int x, int y, int moves, long int*iterations, long int* regressions, int board[linhas][colunas]) {
    visit(x, y, moves, board);
    *(iterations)++;

    if(moves == 64) return 1;

    //definir proximos movimentos válidos
    position neighbour_array[8];
    int close_neighbours_amount = getValidNeighbours(neighbour_array, x, y, board);
    
    for(int i = 0; i < close_neighbours_amount; ++i) {
        if(passeio(neighbour_array[i].x, neighbour_array[i].y, moves + 1, iterations, regressions, board)){
            return 1;
        } else {
            *(regressions)++;
        }
    }

    visit(x, y, moves - 1, board);
    return 0;
}