
#include <cbase/string.h>
#include <stdio.h>

int main() {

  cb_string_t s = cb_string_from("Eray");

  char first_letter = cb_string_get_at(&s, 0);

  printf("%c\n", first_letter);
  return 0;
}
