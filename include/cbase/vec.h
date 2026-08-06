#ifndef CBVEC_H
#define CBVEC_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t capacity;
    size_t len;
} cb_vec_t;

//Instances
cb_vec_t cb_vec_new(void);
cb_vec_t cb_vec_new_with_capacity(size_t cap);

//"Methods"
cb_vec_t cbvec_push(cb_vec_t *self, const int *value);
void cb_vec_print(cb_vec_t *self);
void cb_vec_free(cb_vec_t *self);

#endif
