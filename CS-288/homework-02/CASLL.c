#include <stdio.h>
#include <stdlib.h>

/* self-referential structure */
struct Node {
  int **items;
  struct Node *next;
};

struct List {
  int nodeCapacity;
  struct Node *head;
  struct Node *tail;
};

struct List SLL_new(int nodeCapacity) {
  /* construct an empty list */
  struct List list;
  list.nodeCapacity = nodeCapacity;
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

/* remove and return the first item of the list */
int SLL_pop(struct List *list) {

  struct Node *node = list->head;
  int *items = node->items;

  /* find the first item to pop */
  int item, i;
  for (i = 0; i < list->nodeCapacity; i++) {
    if (&node->items[i] != NULL) {
      item = node->items[i];
    }

    /* popped the last item in the array, array is now empty */
    if (i == list->nodeCapacity - 1) {
      list->head = node->next;
      free(node);
    }
  }

  if (SLL_empty(list)) {
    list->tail = NULL;
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

  int capacity = list->nodeCapacity, i;

  struct Node *node = malloc(sizeof(struct Node));

  int headIsFull = 1;

  /* determine if head items are full */
  if (!SLL_empty(list)) {
    for (i = 0; i < capacity; i++) {
      if (&list->head->items[i] == NULL) {
        headIsFull = 0;
        break;
      }
    }
  }

  if (SLL_empty(list) || headIsFull) {

    /* allocate memory for the items array */
    int *data = malloc(capacity * sizeof(int));

    data[0] = item;

    node->items = data;

    int j;
    for (j = 0; j < capacity; j++) {
      if (node->items[i]) {
        printf("item: %d\n", node->items[i]);
      } else {
        printf("NULL\n");
      }
    }

    /* if head is full, set node as the new head */
    if (headIsFull) {
      node->next = list->head;
      list->head = node;
    }

    /* if list is empty, set head and tail */
    else if (SLL_empty(list)) {
      list->head = node;
      list->tail = node;
    }

    return;
  }

  /* iterate over the items and insert the item */
  for (i = 0; i < list->nodeCapacity; i++) {
    if (&list->head->items[i] == NULL) {
      list->head->items[i] = item;
      break;
    }
  }
}

/* append the item to the end of the list */
void SLL_append(struct List *list, int item) {

  if (SLL_empty(list)) {
    SLL_push(list, item);
    return;
  }

  int capacity = list->nodeCapacity, i;

  struct Node *node = malloc(sizeof(struct Node));

  int tailIsFull = 1;

  /* determine if tail items are full */
  if (!SLL_empty(list)) {
    for (i = 0; i < capacity; i++) {
      if (&list->tail->items[i] == NULL) {
        tailIsFull = 0;
        break;
      }
    }
  }

  if (tailIsFull) {
    /* allocate memory for the items array */
    int *data = malloc(capacity * sizeof(int));
    data[0] = item;

    node->items = data;

    list->tail->next = node;
    list->tail = node;
  } else {
    /* insert the item into the array */
    for (i = 0; i < capacity; i++) {
      if (&list->tail->items[i]) {
        list->tail->items[i] = item;
        break;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  /* if (argc < 3) {
    printf("Missing argc\n");
    exit(1);
  }

  int nodeCapacity = atoi(argv[2]);
  int numItems = atoi(argv[3]); */

  struct List list = SLL_new(2);

  SLL_push(&list, 1);

  /* int i;
  for (i = 0; i < numItems; ++i) {
    SLL_push(&list, i);
    SLL_append(&list, i);
  } */

  while (!SLL_empty(&list)) {
    printf("%d\n", SLL_pop(&list));
  }

  return 0;
}
