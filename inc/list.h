#ifndef LIST_H_
#define LIST_H_

struct list_node {
    struct point p;
    struct list_node *next;
};

struct list {
    struct list_node *head;
    int len;
    int max_size;
};

void list_init(struct list *l, int max_size);
void list_fini(struct list *l);

void list_insert_after(struct list *l, struct list_node *n);

#endif
