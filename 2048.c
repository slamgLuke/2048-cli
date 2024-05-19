#include "2048.h"

void print_matrix(matrix m) {
    for (int i = 0; i < SIZE; i++) {
        for (int ii = 0; ii < (CELL_WIDTH+1)*SIZE; ii++) {
            if (ii % (CELL_WIDTH+1) == 0) printf("+");
            else printf("-");
        }
        puts("+");

        for (int j = 0; j < SIZE; j++) {
            printf("|");
            if (m[i][j] == 0) {
                printf("%*s", CELL_WIDTH, "");
            } else {
                int lskew = 1;
                if (m[i][j] > 1000) lskew = 2;
                printf("%*d%*s", PADDING+lskew, m[i][j], CELL_WIDTH-PADDING-lskew, "");
            }
        }
        puts("|");
    }
    for (int ii = 0; ii < (CELL_WIDTH+1)*SIZE; ii++) {
        if (ii % (CELL_WIDTH+1) == 0) printf("+");
        else printf("-");
    }
    puts("+");
}

void print_score() {
    printf("SCORE: %*d\n", SCORE_PADDING, score);
}

int add_random(matrix m) {
    int empty = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (m[i][j] == 0) empty++;
        }
    }
    if (empty == 0) return 1;
    int r = rand() % empty;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (m[i][j] == 0) {
                if (r == 0) {
                    m[i][j] = (rand() % 2 + 1) << 1;
                    elements++;
                    return 0;
                }
                r--;
            }
        }
    }
    return -1;
}

void init_matrix(matrix m) {
    elements = 0;
    score = 0;
    int to_add = START_TILES;
    int empty = SIZE*SIZE-START_TILES+1;
    int r = rand() % empty;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (r == 0 && to_add > 0) {
                m[i][j] = (rand() % 2 + 1) << 1;
                elements++;
                to_add--;
                empty = SIZE*SIZE - empty;
                r = rand() % empty;
            } else {
                m[i][j] = 0;
                r--;
            }
        }
    }
}

int check_lose(matrix m) {
    if (elements < SIZE*SIZE) return 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i < SIZE-1 && m[i][j] == m[i+1][j]) return 0;
            if (j < SIZE-1 && m[i][j] == m[i][j+1]) return 0;
        }
    }
    return 1;
}

// <--
State move_left(matrix m) {
    State s = NO_MOVE;
    for (int i = 0; i < SIZE; i++) {
        int last = m[i][0];
        int last_index = 0;
        for (int j = 1; j < SIZE; j++) {
            if (m[i][j] == 0) continue;
            if (last == 0) {
                m[i][last_index] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            } else if (last == m[i][j]) {
                m[i][last_index] *= 2;
                last *= 2;
                if (last >= WIN_TILE) s = WIN;
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
                score += last;
                elements--;
            } else {
                if (j == last_index+1) {
                    last = m[i][j];
                    last_index = j;
                    continue;
                }
                last_index++;
                m[i][last_index] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            }
        }
    }
    return s;
}

// -->
State move_right(matrix m) {
    State s = NO_MOVE;
    for (int i = 0; i < SIZE; i++) {
        int last = m[i][SIZE-1];
        int last_index = SIZE-1;
        for (int j = SIZE-2; j >= 0; j--) {
            if (m[i][j] == 0) continue;
            if (last == 0) {
                m[i][last_index] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            } else if (last == m[i][j]) {
                m[i][last_index] *= 2;
                last *= 2;
                if (last >= WIN_TILE) s = WIN;
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
                score += last;
                elements--;
            } else {
                if (j == last_index-1) {
                    last = m[i][j];
                    last_index = j;
                    continue;
                }
                last_index--;
                m[i][last_index] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            }
        }
    }
    return s;
}

// ^
State move_up(matrix m) {
    State s = NO_MOVE;
    for (int j = 0; j < SIZE; j++) {
        int last = m[0][j];
        int last_index = 0;
        for (int i = 1; i < SIZE; i++) {
            if (m[i][j] == 0) continue;
            if (last == 0) {
                m[last_index][j] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            } else if (last == m[i][j]) {
                m[last_index][j] *= 2;
                last *= 2;
                if (last >= WIN_TILE) s = WIN;
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
                score += last;
                elements--;
            } else {
                if (i == last_index+1) {
                    last = m[i][j];
                    last_index = i;
                    continue;
                }
                last_index++;
                m[last_index][j] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            }
        }
    }
    return s;
}

// v
State move_down(matrix m) {
    State s = NO_MOVE;
    for (int j = 0; j < SIZE; j++) {
        int last = m[SIZE-1][j];
        int last_index = SIZE-1;
        for (int i = SIZE-2; i >= 0; i--) {
            if (m[i][j] == 0) continue;
            if (last == 0) {
                m[last_index][j] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            } else if (last == m[i][j]) {
                m[last_index][j] *= 2;
                last *= 2;
                if (last >= WIN_TILE) s = WIN;
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
                score += last;
                elements--;
            } else {
                if (i == last_index-1) {
                    last = m[i][j];
                    last_index = i;
                    continue;
                }
                last_index--;
                m[last_index][j] = m[i][j];
                last = m[i][j];
                m[i][j] = 0;
                s = (s == NO_MOVE) ? MOVE : s;
            }
        }    
    }
    return s;
}



