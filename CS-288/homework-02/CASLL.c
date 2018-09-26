#include <stdio.h>
#include <stdlib.h>

int nodeCapacity;

/* self-referential structure */
/* each node may contain a cluster of nodes */
struct Node {
  int item;
  int vertex;
  struct Node **cluster;
  struct Node *next;
};

struct List {

  struct Node *head;
  struct Node *tail;
};

struct List SLL_new(int nodeCapacity) {
  struct List list;

  list.head = NULL;
  list.tail = NULL;

  return list;
}

/* returns true if cluster has reached the max node capacity */
int clusterIsFull(struct Node **cluster) {
  char hasRoom = 'N';

  int i;
  for (i = 0; i < nodeCapacity; i++) {
    if (cluster[i] == NULL) {
      hasRoom = 'Y';
      break;
    }
  }

  return hasRoom == 'N' ? 1 : 0;
}

/* returns true if cluster is empty */
int clusterIsEmpty(struct Node **cluster) {
  char foundNode = 'N';

  int i;
  for (i = 0; i < nodeCapacity; i++) {
    if (cluster[i]) {
      foundNode = 'Y';
      break;
    }
  }

  return foundNode == 'N' ? 1 : 0;
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

  int vertex = list->head->vertex ? list->head->vertex : 0;

  struct Node *node = malloc(sizeof(struct Node));
  node->item = item;
  node->vertex = vertex;

  /* if list is empty, insert node */
  if (SLL_empty(list)) {
    /* initialize the list */
    list->head->cluster = malloc(list->nodeCapacity * sizeof(struct node *));
    list->head->cluster[0] = node;
  }

  if (clusterIsFull(list->head->cluster, list->nodeCapacity)) {
    /* code goes here */
  } else {
    int i;
    for (i = list->nodeCapacity; i >= 0; i--) {
      /* insert the node */
      if (node->cluster[i] == NULL) {
        node->cluster[i] = node;
        break;
      }
    }
  }

  /* next node */
  node->next = list->head;
  node->next->vertex = node->next->vertex + 1;
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

int main(int argc, char *argv[]) {
  int i;

  if (argc < 4) {
    printf("Missing params\n");
    exit(1);
  }

  int numItems = argv[2];
  int nodeCapacity = argv[3];

  struct List list = SLL_new(nodeCapacity);

  /* insert n items */
  for (i = 0; i < numItems; ++i) {
    SLL_push(&list, i);
    SLL_append(&list, i);
  }

  while (!SLL_empty(&list)) {
    printf("%d\n", SLL_pop(&list));
  }

  return 0;
}
