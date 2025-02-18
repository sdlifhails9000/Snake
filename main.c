#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "snake.h"

int main() {
    WINDOW *mainwin = initscr();
    int rows = 0, cols = 0;
    struct snake s = {};
    clock_t t0 = 0;
    int user_input = 0x00; 

    getmaxyx(mainwin, rows, cols);
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
        }

        /***** Game Logic *****/

        /***** Output *****/
        erase();
        border('|', '|', '-', '-', '+', '+', '+', '+');
        mvhline(2, 1, '-', cols - 2);
        mvprintw(1, 1, "Score: %d", 0);

        refresh();
    }

    endwin();
    return 0;
}


