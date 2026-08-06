/* Demonstrates cbase/vec.h -- the growable int vector.
 *
 * Build with `make`, then run ./build/vec
 *
 * Scope: this walks through allocation and the growth strategy, which is
 * what vec.c implements today. It does not read elements back, because
 * cb_vec_push does not yet store the value it is handed, and the
 * cb_vec_get / cb_vec_set declared in vec.h have no definition yet.
 */
#include <cbase/vec.h>

#include <stdio.h>

static void dump(const char *label, const cb_vec_t *v) {
  printf("%-28s len=%2zu  cap=%2zu\n", label, v->len, v->capacity);
}

int main(void) {
  /* --- Creating -------------------------------------------------------- */
  printf("-- creating --\n");

  /* The default constructor allocates room for 16 ints up front. */
  cb_vec_t v = cb_vec_new();
  dump("cb_vec_new()", &v);

  /* Pick the capacity yourself when you know roughly how much you need,
   * which avoids the reallocations below. */
  cb_vec_t w = cb_vec_new_with_capacity(4);
  dump("cb_vec_new_with_capacity(4)", &w);

  /* --- Growing --------------------------------------------------------- */
  printf("\n-- growing --\n");

  /* push takes the value by pointer. Length rises with every call. */
  for (int i = 0; i < 4; i++) {
    cb_vec_push(&w, &i);
  }
  dump("4x cb_vec_push()", &w);

  /* Once length reaches capacity the buffer is reallocated at twice the
   * size, so pushing stays cheap on average. */
  int fifth = 5;
  cb_vec_push(&w, &fifth);
  dump("1 more push (grows)", &w);

  for (int i = 0; i < 20; i++) {
    cb_vec_push(&v, &i);
  }
  dump("20x push on the default", &v);

  /* --- Cleaning up ----------------------------------------------------- */
  printf("\n-- cleaning up --\n");

  cb_vec_free(&v);
  cb_vec_free(&w);
  printf("%-28s data=%s\n", "cb_vec_free(v)", v.data == NULL ? "NULL" : "set");
  printf("%-28s data=%s\n", "cb_vec_free(w)", w.data == NULL ? "NULL" : "set");

  return 0;
}
