#include "passeio.h"

int board[linhas][colunas] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};

int main () {
    int line, column;
    int position_counter = 1;
    long int iterations = 0;
    long int regressions = 0;

    printf("Type the initial position coordenates of the horse following the format: 'line column', example: 4 5\n");
    scanf("%d", &line);
    scanf("%d", &column);

    if (passeio(line - 1, column - 1, position_counter, &iterations, &regressions, board)) {
        printMatrix(board, iterations, regressions);
    } else {
        printf("\nThe algorithm could not find a solution for these coordinates :(\n");
        return 0;
    }
};