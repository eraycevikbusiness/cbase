#include <cbase/list.h>
#include <stdlib.h>
#include <stdio.h>

cb_ll_t cb_ll_new(void) {
  cb_ll_t ll;
  ll.head = NULL;
  ll.tail = NULL;
  ll.len = 0;
  return ll;
}

void cb_ll_push(cb_ll_t *p, int value) {
  cb_node_t *node = malloc(sizeof(cb_node_t));
  node->value = value;
  node->next = NULL;

  if (p->tail != NULL) {
    p->tail->next = node;
    p->tail = node;
  }

  else {
    p->head = node;
    p->tail = node;
  }

  p->len++;
}

cb_ll_result_t  try_cb_ll_remove_head(cb_ll_t *p) {
  if (p->head == NULL) {
    return HEAD_DOES_NOT_EXIST;
  }

  cb_node_t *next = p->head->next;

  free(p->head);

  p->head = next;
  p->len--;

  return SUCCESS;
}
cb_ll_result_t try_cb_ll_remove_tail(cb_ll_t *p) {
  if (p->tail == NULL) {
    return TAIL_DOES_NOT_EXIST;
  }

  if (p->head == p->tail) {
    free(p->tail);
    p->head = NULL;
    p->tail = NULL;
    p->len = 0;
    return SUCCESS;
  }

  cb_node_t *current = p->head;

  while (current->next != p->tail) {
    current = current->next;
  }

  free(p->tail);
  current->next = NULL;
  p->tail = current;
  p->len--;
  return SUCCESS;
}

void cb_ll_replace_head_by(cb_ll_t *p, int new_value) {
  cb_node_t *new_node = malloc(sizeof(cb_node_t));

  new_node->value = new_value;
  new_node->next = p->head->next;

  free(p->head);

  p->head = new_node;
}

void cb_ll_replace_tail_by(cb_ll_t *p, int new_value) {
  cb_node_t *new_tail = malloc(sizeof(cb_node_t));
  new_tail->value = new_value;
  new_tail->next = NULL;

  if (p->head == p->tail) {

  }

  cb_node_t *current = p->head;

  while (current->next != p->tail) {
    current = current->next;
  }

  free(p->tail);
  current->next = new_tail;
  p->tail = new_tail;
}

cb_ll_result_t try_cb_ll_get_first_node_by_value(cb_ll_t *lp, int value, cb_node_t **res_node) {
  cb_node_t *current = lp->head;

  while (current != NULL) {
    if (current->value == value) {
      *res_node = current;
      return SUCCESS;
    }
    current = current->next;
  }

  return NODE_WITH_PARTICULAR_VALUE_DOES_NOT_EXIST;

}

int cb_ll_contains(cb_ll_t *p, int value) {
  cb_node_t *current = p->head;

  while (current != NULL) {
    if (current->value == value) {
      return 1;
    }

    current = current->next;
  }

  return 0;
}

int cb_ll_count_by(cb_ll_t *p, int value) {
  size_t count = 0;
  cb_node_t *current = p->head;

  while (current != NULL) {
    if (current->value == value) {
      count++;
    }
    current = current->next;
  }

  return count;
}

void cb_ll_print(const cb_ll_t *p, int show_marks) {
  cb_node_t *current = p->head;
  printf("[");
  while (current != NULL) {
    if (current == p->head && show_marks) {
      printf("(HEAD) %d", current->value);
    }else if (current == p->tail && show_marks) {
      printf("(TAIL) %d", current->value);
    }
    else {
      printf("%d", current->value);
    }
    if (current->next != NULL) {
      printf(", ");
    }
    current = current->next;
  }
  printf("] \n");
}


void cb_ll_free(cb_ll_t *p) {
  cb_node_t *current = p->head;

  while (current != NULL) {
    cb_node_t *next = current->next;
    free(current);
    current = next;
  }

  p->len = 0;
}
