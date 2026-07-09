#ifndef CBASE_LINKED_LIST_H
#define CBASE_LINKED_LIST_H

#include <stddef.h>

typedef struct cb_node {
    int value;
    struct cb_node *next;
} cb_node;

typedef struct {
    cb_node *head;
    size_t len;
} cb_ll;

cb_ll cb_ll_new(void);
void cb_ll_push(cb_ll *p, int value);
void cb_ll_print(const cb_ll *p);
void cb_ll_free(cb_ll *p);


#endif
