/* include SLL file */
#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

/*
options:
 - circular array
 - ???
 - don't implement append -20pts
*/

/* global loop variables */
int i, j;

main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Missing args\n");
    exit(1);
  }

  int nodeCapacity = atoi(argv[1]);
  int numItems = atoi(argv[2]);

  for (i = 0; i < 5; i++) {
    printf("%d\n", foo());
  }

  return 0;
}
