/* include SLL file */
#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
options:
 - circular array
 - ???
 - don't implement append -20pts
*/

/* global loop variables */
int i, j;

main(int argc, char const *argv[]) {

  /* start time */
  clock_t start = clock();

  if (argc < 3) {
    printf("Missing args\n");
    exit(1);
  }

  int nodeCapacity = atoi(argv[1]);
  int numItems = atoi(argv[2]);

  struct List list = SLL_new(nodeCapacity);

  /* insert  */
  for (i = 0; i < numItems; ++i) {
    SLL_push(&list, i);
    SLL_append(&list, i);
  }

  /* remove all items in queue */

  /* end time */
  clock_t end = clock();

  double processingTime = (double)(end - start) / CLOCKS_PER_SEC;

  printf("number of items inserted and popped: %d\n", numItems);
  printf("node capacity: %d\n", nodeCapacity);
  printf("time ellapsed: %f\n", processingTime);

  return 0;
}
