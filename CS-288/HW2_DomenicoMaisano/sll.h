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

/* return true if the list contains no items */
int SLL_empty(struct List *list) { return list->head == NULL; }

/* return the number of items in the list */
int SLL_length(struct List *list) {

  struct Node *node;

  int n = 0;

  for (node = list->head; node != NULL; node = node->next) {
    n += node->currentItems;
  }

  return n;
}

/* remove and return the first item of the list */
int SLL_pop(struct List *list) {

  int item;

  if (SLL_empty(list)) {
    printf("List is empty\n");
    list->head = list->tail = NULL;
    return -999;
  }

  /* head is not empty */
  if (!NODE_empty(list->head)) {
    item = NODE_pop(list->head);
  }

  /* if head is empty and there are more nodes */
  if (NODE_empty(list->head) && list->head->next != NULL) {
    struct Node *node = list->head;
    list->head = node->next;

    /* deallocate the node */
    free(node->data);
    free(node);
  }

  /* if head is empty and there are no more nodes  */
  else if (NODE_empty(list->head) && list->head->next == NULL) {
    struct Node *node = list->head;
    list->head = NULL;

    /* deallocate the node */
    free(node->data);
    free(node);
  }

  return item;
}

/* remove all the items from the list */
void SLL_clear(struct List *list) {
  while (!SLL_empty(list)) {
    SLL_pop(list);
  }
}

/* insert the item at the front of the list */
void SLL_push(struct List *list, int item) {

  /* list is empty */
  if (SLL_empty(list)) {
    struct Node *node = NODE_new(list->nodeCapacity);
    NODE_push(node, item);
    list->head = node;
    list->tail = node;
    return;
  }

  /* push to head if there is room */
  else if (!NODE_full(list->head)) {
    NODE_push(list->head, item);
    return;
  }

  /* if head is full, create a new node */
  else {
    struct Node *node = NODE_new(list->nodeCapacity);
    NODE_push(node, item);
    node->next = list->head;
    list->head = node;
    return;
  }
}

/* append the item to the end of the list */
void SLL_append(struct List *list, int item) {

  /* list is empty */
  if (SLL_empty(list)) {
    struct Node *node = NODE_new(list->nodeCapacity);
    NODE_push(node, item);
  }

  /* append to tail if there is room */
  else if (!NODE_full(list->head)) {
    NODE_append(list->head, item);
  }

  /* if tail is full, create a new node */
  else {
    struct Node *node = NODE_new(list->nodeCapacity);
    NODE_append(node, item);
    list->tail->next = node;
    node->next = list->head;
    list->head = node;
  }
}

#endif
