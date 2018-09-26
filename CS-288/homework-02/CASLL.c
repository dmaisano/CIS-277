#include <stdio.h>
#include <stdlib.h>

/* global constants */
static int *NODE_CAPACITY;
static int *NUM_ITEMS;

/* self-referential structure */
struct Node {
  int item;
  struct Node *next;
};

struct List {
  struct Node *head;
  struct Node *tail;
};

struct List SLL_new() {
  /* construct an empty list */
  struct List list;
  list.head = NULL;
  list.tail = NULL;
  return list;
}

int SLL_length(struct List *list) {
  /* return the number of items in the list */
  struct Node *p;

  int n = 0;
  for (p = list->head; p != NULL; p = p->next) {
    ++n;
  }
  return n;
}

int SLL_empty(struct List *list) {
  /* return true if the list contains no items */
  return list->head == NULL;
}

int SLL_pop(struct List *list) {
  /* remove and return the first item of the list */
  struct Node *node = list->head;
  int item = node->item;
  list->head = node->next;
  if (SLL_empty(list)) {
    list->tail = NULL;
  }
  free(node);
  return item;
}

void SLL_clear(struct List *list) {
  /* remove all the items from the list */
  while (!SLL_empty(list)) {
    SLL_pop(list);
  }
}

void SLL_push(struct List *list, int item) {
  /* insert the item at the front of the list */
  struct Node *node = malloc(sizeof(struct Node));
  node->item = item;
  node->next = list->head;
  if (SLL_empty(list)) {
    list->tail = node;
  }
  list->head = node;
}

void SLL_append(struct List *list, int item) {
  /* append the item to the end of the list */
  if (SLL_empty(list)) {
    SLL_push(list, item);
  } else {
    struct Node *node = malloc(sizeof(struct Node));
    node->item = item;
    node->next = NULL;
    list->tail->next = node;
    list->tail = node;
  }
}

int main(int argc, int argv) {
  int i;

  struct List list = SLL_new();
  for (i = 0; i < 5; ++i) {
    SLL_push(&list, i);
    SLL_append(&list, i);
  }

  while (!SLL_empty(&list)) {
    printf("%d\n", SLL_pop(&list));
  }

  return 0;
}
