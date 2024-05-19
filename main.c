#include <time.h>
#include "2048.h"
#include "term_manip.h"

static matrix m = {0};
static int run = 1;

State handle_input(char input) {
    switch(input) {
        case 'a':   return move_left(m);    break;
        case 'd':   return move_right(m);   break;
        case 'w':   return move_up(m);      break;
        case 's':   return move_down(m);    break;
        case 'q':   return QUIT;
        case 'r':   return RESTART;
        default:    return NO_MOVE;
    }
}

void handle_state(State s) {
    switch(s) {
        case NO_MOVE:
            break;
        case MOVE:
            add_random(m);
            break;
        case WIN:
            printf(FLUSH);
            print_score();
            print_matrix(m);
            printf("You win!\n");
            break;
        case LOSE:
            printf(FLUSH);
            print_score();
            print_matrix(m);
            printf("You lose!\n");
            break;
        case QUIT:
            run = 0;
            break;
        case RESTART:
            init_matrix(m);
            break;
    }
}

void debug_state(State s) {
    switch(s) {
        case NO_MOVE:
            printf("NO_MOVE\n");
            break;
        case MOVE:
            printf("MOVE\n");
            break;
        default: break;
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    set_term_mode();
    init_matrix(m);

    State s = NO_MOVE;
    while (run) {
        printf(FLUSH);
        debug_state(s);
        print_score();
        print_matrix(m);
        s = handle_input(getchar());
        s = check_lose(m) ? LOSE : s;
        handle_state(s);
    }
    printf("Closing...\n");
    return 0;
}

