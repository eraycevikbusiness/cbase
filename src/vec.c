#include "cbase/vec.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 16

cb_vec_t cb_vec_new_with_capacity(size_t cap) {
  cb_vec_t vec;
  vec.capacity = cap;
  vec.len = 0;
  vec.data = malloc(sizeof(int) * cap);
  return vec;
}

cb_vec_t cb_vec_new() {
  return cb_vec_new_with_capacity(DEFAULT_CAPACITY);  
}

void cb_vec_push(cb_vec_t *self, const int *value) {
  if (self->len >= self->capacity) {
    //realloc
    size_t new_cap = self->capacity * 2;
    while (new_cap < self->capacity) new_cap *=2;
    self->capacity = new_cap;
    self->data = realloc(self->data, sizeof(int) * new_cap);
  }

  self->data[self->len];
  self->len++;
  
}


void cb_vec_print(const cb_vec_t *self) {
  printf("[");
  for (size_t i = 0; i < self->len; i++) {
    printf("%d", self->data[i]);
    if (i < self->len - 1) {
      printf(", ");
    }
  }
}


void cb_vec_free(cb_vec_t *self) {
  free(self->data);
  self->data = NULL;
  
}
