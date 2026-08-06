#ifndef CBVEC_H
#define CBVEC_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t capacity;
    size_t len;
} cb_vec_t;

typedef enum {
    CB_VEC_RESULT_SUCCESS,
    CB_VEC_RESULT_ERROR_INDEX_OUT_OF_BOUNDS 
} cb_vec_result_t;


//Make instances
cb_vec_t cb_vec_new(void);
cb_vec_t cb_vec_new_with_capacity(size_t cap);

//Methods
void cb_vec_push(cb_vec_t *self, int value);

cb_vec_result_t cb_vec_get(const cb_vec_t *self, size_t index, int *res);
cb_vec_result_t cb_vec_set(cb_vec_t *self, size_t index, int value);

void cb_vec_print(const cb_vec_t *self);
void cb_vec_free(cb_vec_t *self);

#endif
