#include <stdio.h>
#include <stdlib.h>
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
    int s1, s2;
    int position_counter = 1;
    long int iterations = 0;
    long int regressions = 0;

    scanf("%d", &s1);
    scanf("%d", &s2);

    passeio(s1, s2, position_counter, &iterations, &regressions, board);

    return 0;
}