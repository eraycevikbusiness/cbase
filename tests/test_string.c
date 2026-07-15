/* Basic smoke tests for the cbase string (cbase/string.h).
 * These only exercise the public API. Run via `make test`. */
#include <cbase/string.h>

#include <assert.h>
#include <stdio.h>

int main(void) {
  cb_string_t s = cb_string_from("Eray");
  assert(cb_string_len(&s) == 4);
  assert(cb_string_get_at(&s, 0) == 'E');
  assert(cb_string_get_at(&s, 3) == 'y');
  assert(cb_string_contains(&s, 'r') == 1);
  assert(cb_string_contains(&s, 'z') == 0);
  assert(cb_string_contains_str(&s, "ray") == 1);
  assert(cb_string_contains_str(&s, "xyz") == 0);
  assert(cb_string_is_empty(&s) == 0);
  cb_string_free(&s);

  cb_string_t b = cb_string_new();
  assert(cb_string_is_empty(&b) == 1);
  cb_string_push(&b, 'a');
  cb_string_push_str(&b, "bc");
  assert(cb_string_len(&b) == 3);
  assert(cb_string_contains_str(&b, "abc") == 1);
  cb_string_clear(&b);
  assert(cb_string_is_empty(&b) == 1);
  cb_string_free(&b);

  printf("string tests passed\n");
  return 0;
}
