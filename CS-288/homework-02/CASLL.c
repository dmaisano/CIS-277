/* include SLL file */
/* #include "sll.h" */
#include <stdio.h>
#include <stdlib.h>

/* define boolean type */
typedef enum { false, true } bool;

/*
options:
 - circular array
 - ???
 - don't implement append -20pts
*/

main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Missing argc\n");
    exit(1);
  }

  int i;
  int nodeCapacity = atoi(argv[1]);
  int numItems = atoi(argv[2]);

  return 0;
}
