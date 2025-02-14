#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

struct SnakeHead {
    int x, y;
};

void draw_snake(WINDOW *win, struct SnakeHead *head) {
    mvwaddch(win, head->y, head->x, '#');
}

int main() {
    int rows = 0, columns = 0;
    struct SnakeHead head = {};
    WINDOW *main_scr = initscr();
    
    /* Some initial setup. */

    cbreak();  /* Turns off line buffering, but it doesnt
                  turn off interpretation of signal
                  generating characters unlike raw(). */

    noecho();
    keypad(main_scr, TRUE);
    border('|', '|', '-', '-', '/', '\\', '\\', '/');
    
    getmaxyx(main_scr, rows, columns);
    head.x = columns/2;
    head.y = rows/2;

    while (1) {
        draw_snake(main_scr, &head);
        refresh();
    }

    endwin();

    return 0;
}


