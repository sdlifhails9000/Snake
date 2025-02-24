#include <stdlib.h>

#include "list.h"

void list_init(struct list *l, int max_size) {
    l->max_size = max_size;
    l->head = (struct list_node*)malloc(sizeof(struct list_node));
    l->len = 1;
}

void list_fini(struct list *l) {
    struct list_node *iter = l->head, *next = NULL;
    for (int i = 0; iter != NULL; i++) {
        next = iter->next;
        free(iter);
        iter = next;
    }

    l->head = NULL;
    l->max_size = 0;
    l->len = 0;
}

void insert(struct list *l, struct list_node *n) {
    struct list_node *new_node = (struct list_node*)malloc(sizeof(struct list_node));
    new_node->next = n->next;
    n->next = new_node;
}

void pop(struct list *l) {

}

void push(struct list *l, struct point p) {
}

