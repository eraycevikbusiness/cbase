/* Tests for the cbase linked list (cbase/list.h).
 * These only exercise the public API. Run via `make test`. */
#include <cbase/list.h>

#include <assert.h>
#include <stdio.h>

int main(void) {
  /* --- A fresh list is empty ------------------------------------------- */
  cb_ll_t ll = cb_ll_new();
  assert(ll.len == 0);
  assert(ll.head == NULL);
  assert(ll.tail == NULL);

  /* --- push appends at the tail ---------------------------------------- */
  cb_ll_push(&ll, 10);
  assert(ll.len == 1);
  assert(ll.head == ll.tail); /* single node is both ends */

  cb_ll_push(&ll, 20);
  cb_ll_push(&ll, 30); /* [10, 20, 30] */
  assert(ll.len == 3);
  assert(ll.head->value == 10);
  assert(ll.tail->value == 30);
  assert(ll.tail->next == NULL);
  assert(ll.head->next->value == 20); /* insertion order is kept */

  /* --- contains -------------------------------------------------------- */
  assert(cb_ll_contains(&ll, 10) == 1); /* at the head */
  assert(cb_ll_contains(&ll, 30) == 1); /* at the tail */
  assert(cb_ll_contains(&ll, 20) == 1); /* in the middle */
  assert(cb_ll_contains(&ll, 99) == 0);

  /* --- count_by counts every occurrence -------------------------------- */
  cb_ll_push(&ll, 20); /* [10, 20, 30, 20] */
  assert(ll.len == 4);
  assert(cb_ll_count_by(&ll, 20) == 2);
  assert(cb_ll_count_by(&ll, 10) == 1);
  assert(cb_ll_count_by(&ll, 99) == 0);

  /* --- get_first_node_by_value returns the first match ----------------- */
  cb_node_t *found = NULL;
  assert(try_cb_ll_get_first_node_by_value(&ll, 20, &found) == SUCCESS);
  assert(found != NULL);
  assert(found->value == 20);
  assert(found == ll.head->next); /* the earlier 20, not the later one */

  found = NULL;
  assert(try_cb_ll_get_first_node_by_value(&ll, 99, &found) ==
         NODE_WITH_PARTICULAR_VALUE_DOES_NOT_EXIST);
  assert(found == NULL); /* left untouched on failure */

  /* --- replace swaps a value without changing the length --------------- */
  cb_ll_replace_head_by(&ll, 11); /* [11, 20, 30, 20] */
  assert(ll.head->value == 11);
  assert(ll.len == 4);
  assert(cb_ll_contains(&ll, 10) == 0);

  cb_ll_replace_tail_by(&ll, 99); /* [11, 20, 30, 99] */
  assert(ll.tail->value == 99);
  assert(ll.tail->next == NULL);
  assert(ll.len == 4);

  /* --- removing from both ends ----------------------------------------- */
  assert(try_cb_ll_remove_head(&ll) == SUCCESS); /* [20, 30, 99] */
  assert(ll.head->value == 20);
  assert(ll.len == 3);

  assert(try_cb_ll_remove_tail(&ll) == SUCCESS); /* [20, 30] */
  assert(ll.tail->value == 30);
  assert(ll.tail->next == NULL);
  assert(ll.len == 2);

  cb_ll_free(&ll);
  assert(ll.len == 0);

  /* --- an empty list reports why it cannot do anything ------------------ */
  cb_ll_t empty = cb_ll_new();
  assert(try_cb_ll_remove_head(&empty) == HEAD_DOES_NOT_EXIST);
  assert(try_cb_ll_remove_tail(&empty) == TAIL_DOES_NOT_EXIST);
  assert(cb_ll_contains(&empty, 1) == 0);
  assert(cb_ll_count_by(&empty, 1) == 0);

  cb_node_t *none = NULL;
  assert(try_cb_ll_get_first_node_by_value(&empty, 1, &none) ==
         NODE_WITH_PARTICULAR_VALUE_DOES_NOT_EXIST);
  assert(none == NULL);

  printf("list tests passed\n");
  return 0;
}
