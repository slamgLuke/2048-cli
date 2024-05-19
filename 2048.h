#ifndef _2048_H
#define _2048_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
#define CELL_WIDTH 6
#define PADDING CELL_WIDTH / 2
#define SCORE_PADDING CELL_WIDTH * SIZE - 2
#define WIN_TILE 2048
#define START_TILES 2

typedef int matrix[SIZE][SIZE];

typedef enum State {
    NO_MOVE,
    MOVE,
    WIN,
    LOSE,
    QUIT,
    RESTART
} State;

static int score = 0;
static int elements = 0;

void print_matrix(matrix);
void print_score();

int add_random(matrix);
void init_matrix(matrix);

int check_lose(matrix);

State move_left(matrix);
State move_right(matrix);
State move_up(matrix);
State move_down(matrix);

#endif
