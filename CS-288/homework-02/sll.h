#ifndef SLL_H
#define SLL_H

#include "node.h"
#include <stdio.h>
#include <stdlib.h>

/* self-referential structure */
/* each node contains a circular array */
struct Node {
  int front, rear;
  int capacity;
  int *data;
  struct Node *next;
};

struct Node *createNode(int nodeCapacity) {
  struct Node *node;
  node->front = -1;
  node->rear = -1;
  node->capacity = nodeCapacity;
  node->data = (int *)malloc(nodeCapacity * sizeof(int));
  node->next = NULL;
  return node;
};

bool nodeIsEmpty(struct Node *node) {
  /* return true if node queue is empty */
  return node->front == -1 ? true : false;
}

bool nodeIsFull(struct Node *node) {
  /* return true if node queue is full */
  if ((node->front == 0 && node->rear == node->capacity - 1) || (node->rear == (node->front - 1) % (node->capacity - 1))) {
    return true;
  }

  return false;
}

/* add an item to the circular array */
void enQueue(struct Node *node, int item) {
  /* placeholder */
  if (nodeIsFull(node)) {
    printf("\n Queue is full!! \n");
  }

  /* insert first element */
  else if (node->front == -1) {
    node->front = node->rear = 0;
    node->data[node->rear] = item;
  }

  /* If rear becomes the last item in the Queue and the front is not zero,
  set the rear as the front */
  else if (node->front != 0 && node->rear == (node->capacity - 1)) {
    node->rear = 0;
    node->data[node->rear] = item;
  }

  // Increments the rear and adds the num to the end (rear) of the Queue
  else {
  }
}

struct List {
  struct Node *head;
  struct Node *tail;
};

#endif
