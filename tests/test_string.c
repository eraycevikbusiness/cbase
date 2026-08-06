/* Tests for the cbase string (cbase/string.h).
 * These only exercise the public API. Run via `make test`. */
#include <cbase/string.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  /* --- from / new ------------------------------------------------------ */
  cb_string_t s = cb_string_from("Eray");
  assert(cb_string_len(&s) == 4);
  assert(cb_string_is_empty(&s) == 0);
  assert(strcmp(cb_string_as_cstr(&s), "Eray") == 0);

  cb_string_t e = cb_string_new();
  assert(cb_string_len(&e) == 0);
  assert(cb_string_is_empty(&e) == 1);
  assert(strcmp(cb_string_as_cstr(&e), "") == 0);

  /* --- indexing -------------------------------------------------------- */
  assert(cb_string_get_at(&s, 0) == 'E');
  assert(cb_string_get_at(&s, 3) == 'y');

  /* --- clone is independent of the original ---------------------------- */
  cb_string_t c = cb_string_clone(&s);
  assert(cb_string_equals(&s, &c) == 1);
  assert(strcmp(cb_string_as_cstr(&c), "Eray") == 0);

  cb_string_push(&c, '!');
  assert(cb_string_equals(&s, &c) == 0); /* differ once one is changed */
  assert(cb_string_len(&s) == 4);        /* original untouched */
  assert(strcmp(cb_string_as_cstr(&c), "Eray!") == 0);

  /* --- equals compares content, not identity --------------------------- */
  cb_string_t same = cb_string_from("Eray");
  assert(cb_string_equals(&s, &same) == 1);
  cb_string_t shorter = cb_string_from("Era");
  assert(cb_string_equals(&s, &shorter) == 0); /* differing lengths */

  /* --- push / push_str ------------------------------------------------- */
  cb_string_t b = cb_string_new();
  cb_string_push(&b, 'a');
  cb_string_push_str(&b, "bc");
  assert(cb_string_len(&b) == 3);
  assert(strcmp(cb_string_as_cstr(&b), "abc") == 0);

  cb_string_push_str(&b, ""); /* appending nothing changes nothing */
  assert(cb_string_len(&b) == 3);

  /* --- the buffer grows on demand -------------------------------------- */
  cb_string_t g = cb_string_new();
  for (int i = 0; i < 100; i++) {
    cb_string_push(&g, 'x');
  }
  assert(cb_string_len(&g) == 100);
  assert(g.capacity > 100);                     /* grew past the initial 16 */
  assert(cb_string_as_cstr(&g)[99] == 'x');     /* last char is in place */
  assert(cb_string_as_cstr(&g)[100] == '\0');   /* still terminated */

  /* from() sizes the buffer to the input rather than to the default. */
  cb_string_t big = cb_string_from("0123456789abcdefghij"); /* 20 chars */
  assert(cb_string_len(&big) == 20);
  assert(big.capacity > 20);
  assert(strcmp(cb_string_as_cstr(&big), "0123456789abcdefghij") == 0);

  /* --- contains -------------------------------------------------------- */
  assert(cb_string_contains(&s, 'E') == 1); /* first char */
  assert(cb_string_contains(&s, 'y') == 1); /* last char */
  assert(cb_string_contains(&s, 'z') == 0);
  assert(cb_string_contains(&e, 'a') == 0); /* empty contains nothing */

  assert(cb_string_contains_str(&s, "Eray") == 1);  /* whole string */
  assert(cb_string_contains_str(&s, "ray") == 1);   /* suffix */
  assert(cb_string_contains_str(&s, "Er") == 1);    /* prefix */
  assert(cb_string_contains_str(&s, "") == 1);      /* empty needle matches */
  assert(cb_string_contains_str(&s, "xyz") == 0);
  assert(cb_string_contains_str(&s, "Erayy") == 0); /* longer than haystack */

  /* --- pop lowers the length ------------------------------------------- */
  cb_string_t p = cb_string_from("abc");
  cb_string_pop(&p);
  assert(cb_string_len(&p) == 2);
  cb_string_pop(&p);
  cb_string_pop(&p);
  assert(cb_string_is_empty(&p) == 1);
  cb_string_pop(&p); /* popping an empty string is a no-op */
  assert(cb_string_len(&p) == 0);

  /* --- clear empties the string but keeps it usable -------------------- */
  cb_string_clear(&b);
  assert(cb_string_is_empty(&b) == 1);
  assert(strcmp(cb_string_as_cstr(&b), "") == 0);
  cb_string_push_str(&b, "again");
  assert(strcmp(cb_string_as_cstr(&b), "again") == 0);

  cb_string_free(&s);
  cb_string_free(&e);
  cb_string_free(&c);
  cb_string_free(&same);
  cb_string_free(&shorter);
  cb_string_free(&b);
  cb_string_free(&g);
  cb_string_free(&big);
  cb_string_free(&p);

  printf("string tests passed\n");
  return 0;
}
