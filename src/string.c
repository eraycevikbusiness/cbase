#include <cbase/string.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 16

static size_t cb_strlen(char *src) {
  size_t len = 0;

  while (src[len] != '\0') {
    len++;
  }

  return len;
}

static int cb_string_reserve(cb_string_t *p, size_t needed) {
  if (needed <= p->capacity) return 1;
  size_t new_cap = p->capacity * 2;
  while (needed > new_cap) new_cap *= 2;
  char *tmp = realloc(p->data, new_cap);
  if (!tmp) return 0;
  p->data = tmp;
  p->capacity = new_cap;
  return 1;
}

cb_string_t cb_string_new() {
  cb_string_t s;
  s.capacity = DEFAULT_CAPACITY;
  s.len = 0;
  s.data = malloc(DEFAULT_CAPACITY);
  s.data[0] = '\0';

  return s;
}

cb_string_t cb_string_from(char *from) {
  cb_string_t s;
  size_t f_len = cb_strlen(from);
  size_t cap = DEFAULT_CAPACITY;
  while (f_len >= cap) {
    cap *= 2;
  }
  s.len = f_len;
  s.capacity = cap;
  s.data = malloc(cap);

  for (size_t i = 0; i < s.len; i++) {
    s.data[i] = from[i];
  }

  s.data[s.len] = '\0';

  
  return s;
}

void cb_string_push(cb_string_t *p, char c) {
  if (!cb_string_reserve(p, p->len + 2)) return;
  p->data[p->len++] = c;
  p->data[p->len] = '\0';
}

void cb_string_push_str(cb_string_t *p, char *s) {
  size_t s_len = cb_strlen(s);
  if (!cb_string_reserve(p, p->len + s_len + 1)) return;
  for (size_t i = 0; i < s_len;i++) {
    p->data[p->len++] = s[i];
  }

  p->data[p->len] = '\0';
}

int cb_string_contains(cb_string_t *p, char c) {
  for (size_t i = 0; i < p->len; i++) {
    if (p->data[i] == c) {
      return 1;
    }
  }

  return 0;
}

int cb_string_contains_str(cb_string_t *p, char *s) {
  size_t s_len = cb_strlen(s);
  if (s_len == 0) return 1;
  if (s_len > p->len) return 0;
  
  for (size_t i = 0; i + s_len <= p->len; i++) {
    
    size_t j = 0;
    while (j < s_len && p->data[i + j] == s[j]) j++;
    if (j == s_len) return 1;
  }
  return 0;
}

int cb_string_is_empty(cb_string_t *p) {
  return p->len == 0;
}

size_t cb_string_len(cb_string_t *p) {
  return p->len;
}

char cb_string_get_at(cb_string_t *p, size_t index) {
  if (index > p->len) {
    perror("Index is out of bounds");
  }
  return p->data[index];
}

void cb_string_clear(cb_string_t *p) {
  p->len = 0;
  p->data[0] = '\0'; 
}

void cb_string_print(cb_string_t *p) {
  printf("%s \n", p->data);
}

void cb_string_free(cb_string_t *p) {
  free(p->data);
  p->data = NULL;
}


