/* Tests for the cbase vector (cbase/vec.h).
 * These only exercise the public API. Run via `make test`.
 *
 * Scope: allocation and the growth strategy. Element values are not
 * asserted, because cb_vec_push does not yet store the value it is handed,
 * and cb_vec_get / cb_vec_set are declared in vec.h but not defined. */
#include <cbase/vec.h>

#include <assert.h>
#include <stdio.h>

int main(void) {
  /* --- the default constructor reserves room up front ------------------ */
  cb_vec_t v = cb_vec_new();
  assert(v.len == 0);
  assert(v.capacity == 16);
  assert(v.data != NULL);

  /* --- an explicit capacity is honoured --------------------------------- */
  cb_vec_t w = cb_vec_new_with_capacity(4);
  assert(w.len == 0);
  assert(w.capacity == 4);
  assert(w.data != NULL);

  /* --- push raises the length ------------------------------------------ */
  for (int i = 0; i < 4; i++) {
    cb_vec_push(&w, i);
  }
  assert(w.len == 4);
  assert(w.capacity == 4); /* exactly full, no growth needed yet */

  /* --- the buffer doubles once it is full ------------------------------ */
  int fifth = 5;
  cb_vec_push(&w, fifth);
  assert(w.len == 5);
  assert(w.capacity == 8);

  /* --- growth keeps up over many pushes -------------------------------- */
  for (int i = 0; i < 20; i++) {
    cb_vec_push(&v, i);
  }
  assert(v.len == 20);
  assert(v.capacity == 32);
  assert(v.capacity >= v.len); /* the invariant that makes push safe */

  /* --- get particular index */
  cb_vec_t x = cb_vec_new();
  cb_vec_push(&x, 10);
  int x_data_res;
  cb_vec_result_t x_res = cb_vec_get(&x, 0, &x_data_res);
  assert(x_res == CB_VEC_RESULT_SUCCESS && x_data_res == 10);

  
  /* --- set particular index */
  cb_vec_t z = cb_vec_new();
  cb_vec_push(&z, 10);
  cb_vec_result_t z_res = cb_vec_set(&z, 0, 100);
  assert(z_res == CB_VEC_RESULT_SUCCESS && z.data[0] == 100);

  /* --- free clears the data pointer ------------------------------------ */
  cb_vec_free(&v);
  cb_vec_free(&w);
  cb_vec_free(&x);
  cb_vec_free(&z);
  assert(v.data == NULL);
  assert(w.data == NULL);
  assert(x.data == NULL);
  assert(z.data == NULL);
  
  printf("vec tests passed\n");
  return 0;
}
