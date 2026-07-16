#ifndef CBASE_LINKED_LIST_H
#define CBASE_LINKED_LIST_H

#include <stddef.h>

typedef struct cb_node {
    int value;
    struct cb_node *next;
} cb_node_t;

typedef struct {
    cb_node_t *head;
    cb_node_t *tail;
    size_t len;
} cb_ll_t;

typedef enum {
    SUCCESS,
    HEAD_DOES_NOT_EXIST,
    TAIL_DOES_NOT_EXIST,
    NODE_WITH_PARTICULAR_VALUE_DOES_NOT_EXIST
} cb_ll_result_t;

cb_ll_t cb_ll_new(void);

cb_ll_result_t try_cb_ll_remove_head(cb_ll_t *p);
cb_ll_result_t try_cb_ll_remove_tail(cb_ll_t *p); 
cb_ll_result_t try_cb_ll_get_first_node_by_value(cb_ll_t *lp, int value, cb_node_t **res_node);

int cb_ll_contains(cb_ll_t *p, int value);
int cb_ll_count_by(cb_ll_t *p, int value);

void cb_ll_replace_head_by(cb_ll_t *p, int new_value);
void cb_ll_replace_tail_by(cb_ll_t *p, int new_value);
void cb_ll_push(cb_ll_t *p, int value);
void cb_ll_print(const cb_ll_t *p, int show_marks);
void cb_ll_free(cb_ll_t *p);

#endif
