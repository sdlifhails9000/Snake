#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdbool.h>

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct point {
    int x;
    int y;
};

struct player {
    struct point *body;
    int length;
    bool is_dead;
    enum direction direction;
};

void init_player(struct player *player, int max_length);
void fini_player(struct player *player);

void add_segment(struct player *player);

void update_body(struct player *player);

#endif

