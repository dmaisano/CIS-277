#ifndef NODE_H
#define NODE_H

/* reference: https://www.geeksforgeeks.org/implementation-deque-using-circular-array/ */

/* define bool type / macro */
#define bool int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>

/* global loop variables */
int i, j;

/* self-referential structure */
/* each node contains a circular array */
struct Node {
  int front, rear;
  int nodeCapacity, currentItems;
  int *data;
  struct Node *next;
};

/* sets an int item to NULL pointer */
setItemNull(int *item) { item = NULL; }

/* allocates memory for a node and returns it */
struct Node *createNode(int nodeCapacity) {
  struct Node *node;
  node = malloc(sizeof(struct Node));
  node->front = -1;
  node->rear = -1;
  node->nodeCapacity = nodeCapacity;
  node->data = malloc(nodeCapacity * sizeof(int));
  node->next = NULL;
  return node;
};

/* return true if node queue is empty */
bool NODE_empty(struct Node *node) { return node->front == -1; }

/* return true if node queue is full */
bool NODE_full(struct Node *node) { return ((node->front == 0 && node->rear == node->nodeCapacity - 1) || node->front == node->rear + 1); }

/* push an item to the front of the queue */
void NODE_push(struct Node *node, int item) {

  /* if queue is empty */
  if (NODE_empty(node)) {
    node->front = node->rear = 0;
  }

  /* wrap the front to the rear */
  else if (node->front == 0) {
    node->front = node->nodeCapacity - 1;
  }

  else {
    (node->front)++;
  }

  /* increment current number of items in queue */
  (node->currentItems)++;
  node->data[node->front] = item;
}

/* append an item to the front of the queue */
void NODE_append(struct Node *node, int item) {

  /* if queue is empty */
  if (NODE_empty(node)) {
    node->front = node->rear = 0;
  }

  /* wrap the rear to the front */
  else if (node->rear == node->nodeCapacity - 1) {
    node->rear = 0;
  }

  else {
    (node->rear)++;
  }

  /* increment current number of items in queue */
  (node->currentItems)++;
  node->data[node->rear] = item;
}

/* pops a number from the queue */
int NODE_pop(struct Node *node) {
  int num;

  /* placeholder, need to remove*/
  if (NODE_empty(node)) {
    return -999;
  }

  /* queue has only one item */
  /* reset queue to rmpty state */
  if (node->front == node->rear) {
    num = node->data[node->front];
    node->front = node->rear = -1;
  }

  /* wrap the front around */
  else if (node->front == node->nodeCapacity - 1) {
    num = node->data[node->front];
    node->front = 0;
  }

  /* increment by one */
  else {
    num = node->data[node->front];
    (node->front)++;
  }

  /* decrement current number of items in queue */
  --(node->currentItems);
  return num;
}

#endif
