#include <stdio.h>
#include <stdlib.h>

struct Queue {
  int front, rear;
  int capacity;
  int *data;
};

struct Queue createQueue(int nodeCapacity) {
  struct Queue queue;
  queue.front = -1;
  queue.rear = -1;
  queue.capacity = nodeCapacity;
  queue.data = malloc(nodeCapacity * sizeof(int));
}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
