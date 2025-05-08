#include <ncurses.h>
#include <stdlib.h> /* srandom(), random(), malloc(), free() */
#include <time.h> /* clock_t, clock(), time() */
#include <stdbool.h>

#include "snake.h"

struct point generate_food(int max_rows, int max_cols) {
    struct point retval = {0};
    do {
        retval.x = random() % (max_cols - 4) + 1;
        retval.y = random() % (max_rows - 6) + 3;
    } while (mvinch(retval.y, retval.x) == 'O' || mvinch(retval.y, retval.x) == '#');

    return retval;
}

enum direction key_to_direction(int input) {
    switch (input) {
    case 'w':
        return UP;
    case 'a':
        return LEFT;
    case 's':
        return DOWN;
    case 'd':
        return RIGHT;
    default:
        return -1;
    }
}

int main() {
    WINDOW *mainwin = initscr();
    int MAX_ROWS = 0, MAX_COLS = 0;

    char body_seg = ' ';
    clock_t t0 = 0;
    int user_input = 0;
    enum direction new_dir = 0;
    
    struct player p = {};

    getmaxyx(mainwin, MAX_ROWS, MAX_COLS);

    init_player(&p, MAX_ROWS * MAX_COLS);
    p.body[0] = (struct point){ .x=(int)(MAX_COLS / 2), .y=(int)(MAX_ROWS / 2) };
    p.body[1] = (struct point){ .x=(int)(MAX_COLS / 2 - 1), .y=(int)(MAX_ROWS / 2) };
    p.length = 2;

    srandom(time(NULL));
    cbreak();
    noecho();
    curs_set(0);
    keypad(mainwin, true);
    nodelay(mainwin, true);

    struct point food = {
        .x = (int)(MAX_COLS / 2) + 5,
        .y = (int)(MAX_ROWS / 2)
    };

    while (!p.is_dead) {
        /***** Input and timing *****/
        t0 = clock();
        while (clock() - t0 <= 250000) {
            user_input = getch();
            if (user_input == ERR)
                continue;
            
            if ((int)(new_dir = key_to_direction(user_input)) == -1)
                continue;

            /* check if new and old direction are parallel */
            if (((p.direction + new_dir) & 0x1) == 0)
                continue;

            p.direction = new_dir;
            break;
        }

        /***** Game Logic *****/
        update_body(&p);

        switch (mvinch(p.body[0].y, p.body[0].x)) {
        case '*':
            add_segment(&p);
            food = generate_food(MAX_ROWS, MAX_COLS);
            break;
        case '#':
        case '-':
        case '|':
            p.is_dead = true;
        }

        /***** Output *****/
        erase();
        border('|', '|', '-', '-', '+', '+', '+', '+');
        mvhline(2, 1, '-', MAX_COLS - 2);
        mvprintw(1, 1, "Score: %d", p.length-1);

        mvaddch(food.y, food.x, '*');

        body_seg = p.is_dead ? '+' : '#';
        for (int i = 1; i < p.length; i++)
            mvaddch(p.body[i].y, p.body[i].x, body_seg);

        mvaddch(p.body[0].y, p.body[0].x, p.is_dead ? 'X' : 'O');

        refresh();
    }

    nodelay(mainwin, false);
    mvprintw(1, (int)(MAX_COLS/2),"You've lost");
    getch();
   
    endwin();
    fini_player(&p);

    return 0;
}

