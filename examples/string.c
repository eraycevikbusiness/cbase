/* Demonstrates cbase/string.h -- the growable string.
 *
 * Build with `make`, then run ./build/string
 */
#include <cbase/string.h>

#include <stdio.h>

static void dump(const char *label, const cb_string_t *s) {
  printf("%-22s \"%s\"  len=%zu cap=%zu\n", label, cb_string_as_cstr(s),
         cb_string_len(s), s->capacity);
}

int main(void) {
  /* --- Creating -------------------------------------------------------- */
  printf("-- creating --\n");

  /* An empty string still allocates a buffer, so it is usable right away. */
  cb_string_t empty = cb_string_new();
  dump("cb_string_new()", &empty);
  printf("%-22s %d\n", "is_empty()", cb_string_is_empty(&empty));

  cb_string_t s = cb_string_from("Eray");
  dump("cb_string_from(\"Eray\")", &s);
  printf("%-22s %d\n", "is_empty()", cb_string_is_empty(&s));

  /* clone copies the contents into a fresh allocation, so the two strings
   * are independent afterwards. */
  cb_string_t copy = cb_string_clone(&s);
  dump("cb_string_clone(s)", &copy);
  printf("%-22s %d\n", "equals(s, copy)", cb_string_equals(&s, &copy));

  /* --- Appending ------------------------------------------------------- */
  printf("\n-- appending --\n");

  cb_string_push(&copy, '!');
  dump("push('!')", &copy);
  printf("%-22s %d\n", "equals(s, copy)", cb_string_equals(&s, &copy));

  cb_string_push_str(&copy, " Cevik");
  dump("push_str(\" Cevik\")", &copy);

  /* The buffer starts at 16 bytes and doubles whenever it runs out, so
   * appending never needs a manual resize. */
  printf("\n%-22s cap=%zu\n", "before growth", copy.capacity);
  for (int i = 0; i < 40; i++) {
    cb_string_push(&copy, '.');
  }
  printf("%-22s len=%zu cap=%zu\n", "after 40x push('.')", cb_string_len(&copy),
         copy.capacity);

  /* --- Reading --------------------------------------------------------- */
  printf("\n-- reading --\n");

  printf("%-22s '%c'\n", "get_at(s, 0)", cb_string_get_at(&s, 0));
  printf("%-22s '%c'\n", "get_at(s, 3)", cb_string_get_at(&s, 3));
  printf("%-22s %zu\n", "len(s)", cb_string_len(&s));

  /* as_cstr hands out the internal buffer, ready for printf and friends. */
  printf("%-22s %s\n", "as_cstr(s)", cb_string_as_cstr(&s));

  printf("%-22s %d\n", "contains(s, 'r')", cb_string_contains(&s, 'r'));
  printf("%-22s %d\n", "contains(s, 'z')", cb_string_contains(&s, 'z'));
  printf("%-22s %d\n", "contains_str(\"ray\")", cb_string_contains_str(&s, "ray"));
  printf("%-22s %d\n", "contains_str(\"xyz\")", cb_string_contains_str(&s, "xyz"));

  /* --- Shrinking ------------------------------------------------------- */
  printf("\n-- shrinking --\n");

  cb_string_t p = cb_string_from("abc");
  dump("from(\"abc\")", &p);

  /* pop lowers the length. Note it leaves the buffer untouched, so the
   * text printed by as_cstr still shows the popped character. */
  cb_string_pop(&p);
  printf("%-22s len=%zu, as_cstr=\"%s\"\n", "pop()", cb_string_len(&p),
         cb_string_as_cstr(&p));

  /* clear resets the length and terminates the buffer, so the string reads
   * as empty again. */
  cb_string_clear(&p);
  dump("clear()", &p);
  printf("%-22s %d\n", "is_empty()", cb_string_is_empty(&p));

  /* --- Printing and cleanup -------------------------------------------- */
  printf("\n-- printing --\n");
  printf("cb_string_print(s):  ");
  cb_string_print(&s);

  cb_string_free(&empty);
  cb_string_free(&s);
  cb_string_free(&copy);
  cb_string_free(&p);

  return 0;
}
