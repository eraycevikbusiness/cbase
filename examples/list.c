/* Demonstrates cbase/list.h -- the singly linked list.
 *
 * Build with `make`, then run ./build/list
 */
#include <cbase/list.h>

#include <stdio.h>

static const char *result_name(cb_ll_result_t r) {
  switch (r) {
  case SUCCESS:
    return "SUCCESS";
  case HEAD_DOES_NOT_EXIST:
    return "HEAD_DOES_NOT_EXIST";
  case TAIL_DOES_NOT_EXIST:
    return "TAIL_DOES_NOT_EXIST";
  case NODE_WITH_PARTICULAR_VALUE_DOES_NOT_EXIST:
    return "NODE_WITH_PARTICULAR_VALUE_DOES_NOT_EXIST";
  }
  return "unknown";
}

int main(void) {
  /* --- Creating and filling ------------------------------------------- */
  printf("-- creating --\n");

  cb_ll_t ll = cb_ll_new();
  printf("cb_ll_new()          len=%zu  ", ll.len);
  cb_ll_print(&ll, 0);

  /* Push appends at the tail, so the list keeps insertion order. */
  for (int i = 1; i <= 5; i++) {
    cb_ll_push(&ll, i * 10);
  }
  printf("5x cb_ll_push()      len=%zu  ", ll.len);
  cb_ll_print(&ll, 0);

  /* The second argument turns on the (HEAD)/(TAIL) labels. */
  printf("...with show_marks   len=%zu  ", ll.len);
  cb_ll_print(&ll, 1);

  /* --- Searching ------------------------------------------------------- */
  printf("\n-- searching --\n");

  printf("contains(30)         %d\n", cb_ll_contains(&ll, 30));
  printf("contains(99)         %d\n", cb_ll_contains(&ll, 99));

  /* count_by counts every occurrence, so push a duplicate to show it. */
  cb_ll_push(&ll, 30);
  printf("after push(30)       ");
  cb_ll_print(&ll, 0);
  printf("count_by(30)         %d\n", cb_ll_count_by(&ll, 30));
  printf("count_by(99)         %d\n", cb_ll_count_by(&ll, 99));

  /* The try_ functions report failure instead of returning a bad pointer.
   * The node is handed back through the out-parameter res_node. */
  cb_node_t *found = NULL;
  cb_ll_result_t r = try_cb_ll_get_first_node_by_value(&ll, 40, &found);
  printf("get_first(40)        %s, node->value=%d\n", result_name(r),
         found->value);

  found = NULL;
  r = try_cb_ll_get_first_node_by_value(&ll, 99, &found);
  printf("get_first(99)        %s, node=%s\n", result_name(r),
         found == NULL ? "NULL" : "set");

  /* --- Replacing ------------------------------------------------------- */
  printf("\n-- replacing --\n");

  /* These swap the value in place; the length does not change. */
  cb_ll_replace_head_by(&ll, 11);
  printf("replace_head_by(11)  len=%zu  ", ll.len);
  cb_ll_print(&ll, 1);

  cb_ll_replace_tail_by(&ll, 99);
  printf("replace_tail_by(99)  len=%zu  ", ll.len);
  cb_ll_print(&ll, 1);

  /* --- Removing -------------------------------------------------------- */
  printf("\n-- removing --\n");

  r = try_cb_ll_remove_head(&ll);
  printf("remove_head()        %s  len=%zu  ", result_name(r), ll.len);
  cb_ll_print(&ll, 0);

  r = try_cb_ll_remove_tail(&ll);
  printf("remove_tail()        %s  len=%zu  ", result_name(r), ll.len);
  cb_ll_print(&ll, 0);

  /* On an empty list the same calls report why they could not do anything. */
  cb_ll_t empty = cb_ll_new();
  printf("remove_head(empty)   %s\n", result_name(try_cb_ll_remove_head(&empty)));
  printf("remove_tail(empty)   %s\n", result_name(try_cb_ll_remove_tail(&empty)));

  /* --- Cleaning up ----------------------------------------------------- */
  cb_ll_free(&ll);
  printf("\ncb_ll_free()         len=%zu\n", ll.len);

  return 0;
}
