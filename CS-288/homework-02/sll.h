#ifndef SLL_H
#define SLL_H

#include "node.h"
#include <stdio.h>
#include <stdlib.h>

/* global loop variables */
int i, j;

struct List {
  int nodeCapacity;
  struct Node *head;
  struct Node *tail;
};

/* construct an empty list */
struct List SLL_new(int nodeCapacity) {
  struct List list;
  list.nodeCapacity = nodeCapacity;
  list.head = NULL;
  list.tail = NULL;
  return list;
}

/* return the number of items in the list */
int SLL_length(struct List *list) {

  struct Node *node;

  int n = 0;

  for (node = list->head; node != NULL; node = node->next) {
    n += node->currentItems;
  }

  return n;
}

#endif
