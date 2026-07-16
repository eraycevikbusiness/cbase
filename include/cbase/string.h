#ifndef CBSTRING_H
#define CBSTRING_H

#include <stddef.h>

typedef struct {
  char *data;
  size_t capacity;
  size_t len;
} cb_string_t;

typedef enum {
  CB_STRING_RESULT_ERROR_MALLOC,
  CB_STRING_RESULT_SUCCESS,  
} cb_string_result_t;

cb_string_t cb_string_new(void);
cb_string_t cb_string_from(const char *from);
cb_string_t cb_string_clone(const cb_string_t *subject);

void cb_string_push(cb_string_t *p, char c);
void cb_string_push_str(cb_string_t *p, const char *s);

int cb_string_contains(const cb_string_t *p, char c);
int cb_string_contains_str(const cb_string_t *p, const char *s);
int cb_string_is_empty(const cb_string_t *p);
int cb_string_equals(const cb_string_t *a, const cb_string_t *b);

size_t cb_string_len(const cb_string_t *p);

char cb_string_get_at(const cb_string_t *p, size_t index);

const char *cb_string_as_cstr(const cb_string_t *p);

void cb_string_pop(cb_string_t *p);
void cb_string_clear(cb_string_t *p);
void cb_string_print(const cb_string_t *p);
void cb_string_free(cb_string_t *p);

#endif
