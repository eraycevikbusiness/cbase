/* Basic smoke tests for the cbase linked list (cbase/list.h).
 * These only exercise the public API. Run via `make test`. */
#include <cbase/list.h>

#include <assert.h>
#include <stdio.h>

int main(void) {
  cb_ll_t ll = cb_ll_new();
  assert(ll.len == 0);
  assert(ll.head == NULL);
  assert(ll.tail == NULL);

  cb_ll_push(&ll, 10);
  cb_ll_push(&ll, 20);
  cb_ll_push(&ll, 30);
  assert(ll.len == 3);
  assert(ll.head->value == 10);
  assert(ll.tail->value == 30);

  assert(cb_ll_contains(&ll, 20) == 1);
  assert(cb_ll_contains(&ll, 99) == 0);

  cb_ll_push(&ll, 20);
  assert(cb_ll_count_by(&ll, 20) == 2);

  cb_node_t *found = NULL;
  assert(try_cb_ll_get_first_node_by_value(&ll, 30, &found) == SUCCESS);
  assert(found != NULL && found->value == 30);

  assert(try_cb_ll_remove_head(&ll) == SUCCESS);
  assert(ll.head->value == 20);

  assert(try_cb_ll_remove_tail(&ll) == SUCCESS);
  assert(ll.tail->value == 30);

  cb_ll_free(&ll);
  assert(ll.len == 0);

  cb_ll_t empty = cb_ll_new();
  assert(try_cb_ll_remove_head(&empty) == HEAD_DOES_NOT_EXIST);
  assert(try_cb_ll_remove_tail(&empty) == TAIL_DOES_NOT_EXIST);

  printf("list tests passed\n");
  return 0;
}
