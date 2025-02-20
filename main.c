#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h> /* clock_t, clock() */
#include <string.h>

enum direction {
    UP, LEFT, DOWN, RIGHT
};

struct point {
    int x, y;
};

struct snake {
    struct point *body;
    int tail;
    int max_length;
    int is_dead;
    enum direction dir;
};

int main() {
    WINDOW *mainwin = initscr();
    int rows = 0, cols = 0; /* Height and width of the window. */
    struct snake s = {}; /* player */
    clock_t t0 = 0;
    int user_input = 0x00;
    const char KEYS_TO_DIR[4][2] = {
        { 'w', UP },
        { 'a', LEFT },
        { 's', DOWN },
        { 'd', RIGHT }
    };
    int is_key_valid = 0;
    enum direction new_dir = 0;

    char aux[5] = {}; /* For testing */

    getmaxyx(mainwin, rows, cols);

    s.max_length = (rows - 4) * (cols - 2);
    s.tail = 1;
    s.is_dead = 0;
    s.body = (struct point*)malloc(s.max_length * sizeof(struct point));
    s.body[0] = (struct point){ .x=(int)(cols / 2), .y=(int)(rows / 2) };
    s.body[1] = (struct point){ .x=(int)(cols / 2 - 1), .y=(int)(rows / 2) };
    s.dir = RIGHT;

    cbreak();
    noecho();
    curs_set(0);
    keypad(mainwin, 1);
    nodelay(mainwin, 1);

    while (1) {
        /***** Input and timing *****/
        t0 = clock();
        while ((clock() - t0) / CLOCKS_PER_SEC <= .25) {
            user_input = getch();
            if (user_input == ERR)
                continue;

            for (int i = 0; i < 4; i++) {
                if ((char)user_input == KEYS_TO_DIR[i][0]) {
                    new_dir = KEYS_TO_DIR[i][1];
                    is_key_valid = 1;
                    break;
                }
            }   

            if (!is_key_valid) {
                is_key_valid = 0;
                continue;
            }

            if (s.dir == new_dir || (s.dir + 2) % 4 == new_dir)
                continue;

            s.dir = new_dir;
            break;
        }

        /***** Game Logic *****/

        /***** Output *****/
        erase();
        border('|', '|', '-', '-', '+', '+', '+', '+');
        mvhline(2, 1, '-', cols - 2);
        mvprintw(1, 1, "Score: %d", s.tail);

        switch (s.dir) {
        case UP:
            strncpy(aux, "UP", 2);
            break;
        case LEFT:
            strncpy(aux, "LEFT", 4);
            break;
        case DOWN:
            strncpy(aux, "DOWN", 4);
            break;
        case RIGHT:
            strncpy(aux, "RIGHT", 5);
            break;
        }

        mvprintw(1, (int)(cols / 2), "Direction: %s", aux);

        memset(aux, 0, 5);
        refresh();
    }

    free(s.body);
    endwin();
    return 0;
}


