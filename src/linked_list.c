#include <cbase/linked_list.h>
#include <stdlib.h>
#include <stdio.h>

cb_ll cb_ll_new(void) {
  cb_ll ll;
  ll.head = NULL;
  ll.len = 0;
}

void cb_ll_push(cb_ll *p, int value) {
  cb_node *node = malloc(sizeof(cb_node));
  node->value = value;
  node->next = NULL;

  cb_node *current = p->head;
  if (current != NULL) {
   
   while (current->next != NULL) {
     current = current->next;
   }

   current->next = node;
      
  }
  else {
    p->head = node;
  }

  p->len++;
}

void cb_ll_print(const cb_ll *p) {
  cb_node *current = p->head;
  printf("[");
  while (current != NULL) {
    printf("%d", current->value);
    if (current->next != NULL) {
      printf(", ");
    }
    current = current->next;
  }
  printf("] \n");
}


void cb_ll_free(cb_ll *p) {
  cb_node *current = p->head;

  while (current != NULL) {
    cb_node *next = current->next;
    free(current);
    current = next;
  }

  p->len = 0;
} 
