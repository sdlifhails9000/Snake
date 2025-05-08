#include <ncurses.h>
#include <stdlib.h>

#include "snake.h"

void init_player(struct player *p, int max_length) {
    p->length = 0;
    p->direction = RIGHT;
    p->is_dead = false;
    p->body = malloc(max_length * sizeof(struct point));
}

void fini_player(struct player *p) {
    free(p->body);
    *p = (struct player){ 0 };
}

void add_segment(struct player *p) {
    p->body[p->length].x = p->body[p->length-1].x;
    p->body[p->length].y = p->body[p->length-1].y;
    p->length++;
}

void update_body(struct player *p) {
    for (int i = p->length - 1; i > 0; i--)
        p->body[i] = p->body[i-1];

    switch (p->direction) {
    case UP:
        p->body[0].y--;
        break;
    case LEFT:
        p->body[0].x--;
        break;
    case DOWN:
        p->body[0].y++;
        break;
    case RIGHT:
        p->body[0].x++;
        break;
    }
}

