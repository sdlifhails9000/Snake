#ifndef SNAKE_H_
#define SNAKE_H_

enum direction {
    UP=0,
    LEFT,
    DOWN,
    RIGHT
};

struct point {
    int x, y;
};

/**
 * Description: a structure representing the player.
 *
 * Members:
 *  body: An array of coordinates representing the body.
 *        body[0] is the head of the snake.
 *  len: Length of the snake body excluding the head.
 *  is_dead: A boolean that determines if the snake is dead or not.
 *  max_len: maximum length of the snake. Depends on the terminal screen.
 */
struct snake {
    struct point *body;
    int max_len;
    int len;
    char is_dead;
    enum direction dir;
};

void init_snake(struct snake *s);
void end_snake(struct snake *s);

void update_snake_body(struct snake *s);
void display_snake(struct snake *s, WINDOW *win);

char snake_is_dead(const struct snake *s);

void add_segment(struct snake *s);

void set_direction(struct snake *s, enum direction dir);
enum direction get_direction(const struct snake *s);


#endif
