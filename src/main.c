#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main() {
    WINDOW *main_scr = initscr();
    cbreak();  /* Turns off line buffering, but it doesnt
                  turn off interpretation of signal
                  genersring characters. */

    noecho();  /* Prevents input character from being
                  printed (echoed) onto the screen. */

    keypad(main_scr, TRUE); /* Turns on interpretation
                               of special chars. */

    /* Draws a border around the window. */
    border('|', '|', '-', '-', '/', '\\', '\\', '/');

    getch();
    endwin();

    return 0;
}

