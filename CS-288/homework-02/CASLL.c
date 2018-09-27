#include <stdio.h>
#include <stdlib.h>

// define boolean type
typedef enum { false, true } bool;

/* self-referential structure */
struct Node {
  int *items; /* a pointer, to an array of int pointers */
  struct Node *next;
};

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

/* TODO: FIX POP */
/* remove and return the first item of the list */
int SLL_pop(struct List *list) {

  /* list is empty, cannot pop */
  if (list->head == NULL) {
    printf("cannot pop empty list\n");
    return -9999;
  }

  struct Node *node = list->head;

  int item, i;

  /* find the first item to pop */
  for (i = 0; i < list->nodeCapacity; i++) {
    if (node->items[i] != NULL) {
      item = node->items[i];
      node->items[i] = NULL;
      break;
    }
  }

  /* for (i = 0; i < list->nodeCapacity; i++) {
    if (node->items[i] != NULL) {
      printf("index %d\titem %d\n", i, node->items[i]);
    } else {
      printf("index %d\tNULL\n", i);
    }
  } */

  int nodeIsEmpty = 1;

  for (i = 0; i < list->nodeCapacity; i++) {
    if (node->items[i] != NULL) {
      nodeIsEmpty = 0;
      break;
    }
  }

  /* popped the last item in the array, array is now empty */
  if (nodeIsEmpty) {
    list->head = node->next;
    /* free(node); */
  }

  if (SLL_empty(list)) {
    list->head = NULL;
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
      if (list->head->items[i] == NULL) {
        headIsFull = 0;
        break;
      }
    }
  }

  if (SLL_empty(list) || headIsFull) {

    /* allocate memory for the new head node */
    int **data = malloc(sizeof(int *) + (capacity * sizeof(int)));

    /* initialize items to NULL */
    int i;
    for (i = 0; i < capacity; i++) {
      data[i] = NULL;
    }

    data[0] = (int *)item;

    node->items = data;

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
  for (i = 0; i < capacity; i++) {
    if (list->head->items[i] == NULL) {
      list->head->items[i] = (int *)item;
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
      if (list->tail->items[i] == NULL) {
        tailIsFull = 0;
        break;
      }
    }
  }

  if (tailIsFull) {
    /* allocate memory for the new tail node */
    int **data = malloc(sizeof(int *) + (capacity * sizeof(int)));

    /* initialize items to NULL */
    for (i = 0; i < capacity; i++) {
      data[i] = NULL;
    }

    data[0] = (int *)item;

    node->items = data;

    list->tail->next = node;
    list->tail = node;
  } else {
    /* append the item into the array */
    for (i = 0; i < capacity; i++) {
      if (list->tail->items[i] == NULL) {
        list->tail->items[i] = (int *)item;
        break;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Missing argc\n");
    exit(1);
  }

  int nodeCapacity = atoi(argv[1]);
  int numItems = atoi(argv[2]);

  struct List list = SLL_new(nodeCapacity);

  SLL_append(&list, 10);
  SLL_push(&list, 20);

  printf("%d\n", SLL_pop(&list));
  printf("%d\n", SLL_pop(&list));

  /* int i;
  for (i = 0; i < numItems; ++i) {
    SLL_push(&list, i);
    SLL_append(&list, i);
  } */

  /* while (!SLL_empty(&list)) {
    printf("%d\n", SLL_pop(&list));
  } */

  return 0;
}
