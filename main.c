#include <ncurses.h>
#include <stdlib.h> /* srandom(), random() */
#include <time.h> /* clock_t, clock() */

enum direction {
    UP, LEFT, DOWN, RIGHT
};

struct point {
    int x, y;
};

int main() {
    WINDOW *mainwin = initscr();
    int MAX_ROWS = 0, MAX_COLS = 0;
    getmaxyx(mainwin, MAX_ROWS, MAX_COLS);

    char body_seg = ' ';
    clock_t t0 = 0;
    int user_input = 0;
    enum direction new_dir = 0;

    struct point *body = (struct point*)malloc(sizeof(struct point));
    body[0] = (struct point){ .x=(int)(MAX_COLS / 2), .y=(int)(MAX_ROWS / 2) };
    body[1] = (struct point){ .x=(int)(MAX_COLS / 2 - 1), .y=(int)(MAX_ROWS / 2) };
    int tail = 1;
    int is_dead = 0;
    enum direction dir = RIGHT;

    srandom(time(NULL));
    cbreak();
    noecho();
    curs_set(0);
    keypad(mainwin, TRUE);
    nodelay(mainwin, TRUE);

    struct point food = {};
    food.x = random() % (MAX_COLS - 4) + 1;
    food.y = random() % (MAX_ROWS - 6) + 3;
    while (!is_dead) {
        /***** Input and timing *****/
        t0 = clock();
        while (clock() - t0 <= 250000) {
            user_input = getch();
            if (user_input == ERR)
                continue;

            switch ((char)user_input) {
            case 'w':
                new_dir = 0;
                break;
            case 'a':
                new_dir = 1;
                break;
            case 's':
                new_dir = 2;
                break;
            case 'd':
                new_dir = 3;
                break;
            default:
                continue;
            }

            /* check if new and old direction are parallel */
            if (((dir + new_dir) & 0x1) == 0)
                continue;

            dir = new_dir;
            break;
        }

        /***** Game Logic *****/
        for (int i = tail; i > 0; i--) {
            body[i] = body[i-1];
        }

        switch (dir) {
        case UP:
            body[0].y--;
            break;
        case LEFT:
            body[0].x--;
            break;
        case DOWN:
            body[0].y++;
            break;
        case RIGHT:
            body[0].x++;
            break;
        }

        is_dead = body[0].x % (MAX_COLS - 1) == 0 ||
            (body[0].y - 2) % (MAX_ROWS - 3) == 0;

        for (int i = 1; i <= tail; i++) {
            if (body[0].x == body[i].x &&
                    body[0].y == body[i].y) {
                is_dead = 1;
                break;
            }
        }

        if (body[0].x == food.x && body[0].y == food.y) {
            tail++;
            body[tail].x = 2*body[tail-1].x - body[tail-2].x;
            body[tail].y = 2*body[tail-1].y - body[tail-2].y;
            food.x = random() % (MAX_COLS - 4) + 1;
            food.y = random() % (MAX_ROWS - 6) + 3;
        }

        /***** Output *****/
        erase();
        border('|', '|', '-', '-', '+', '+', '+', '+');
        mvhline(2, 1, '-', MAX_COLS - 2);
        mvprintw(1, 1, "Score: %d", tail);

        mvaddch(food.y, food.x, '*');

        body_seg = is_dead ? '+' : '#';
        for (int i = 1; i <= tail; i++)
            mvaddch(body[i].y, body[i].x, body_seg);

        mvaddch(body[0].y, body[0].x, is_dead ? 'X' : 'O');

        refresh();
    }

    nodelay(mainwin, FALSE);
    mvprintw(1, (int)(MAX_COLS/2),"You've lost");
    getch();
   
    endwin();
    return 0;
}

