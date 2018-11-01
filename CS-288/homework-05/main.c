#include "merge.h"
#include "radix.h"
#include "selection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int i;
clock_t begin, end;

int *cpyArr(int const *arr, size_t len) {
  int memSize = len * sizeof(int);
  int *cpy = malloc(memSize);

  memcpy(cpy, arr, memSize);

  return cpy;
}

float execTime(clock_t begin, clock_t end) { return (double)(end - begin) / CLOCKS_PER_SEC; }

void writeResults(char *type, int size, float f) {
  FILE *file = fopen("results.txt", "ab+");
  fprintf(file, "%s sort took %fs\n", f);
  fclose(file);
}

void mergeSortTest(int *arr, int low, int high) {
  int size = sizeof(arr) / sizeof(arr[0]);

  begin = clock();
  mergeSort(arr, low, high);
  end = clock();

  printf("merge exec time: %f\n", execTime(begin, end));
}

void radixSortTest(int *arr, int len) {
  begin = clock();
  radixSort(arr, len);
  end = clock();

  printf("radix exec time: %f\n", execTime(begin, end));
}

void selectionSortTest(int *arr, int len) {

  if (len >= 1000000) {
    printf("skipping selection sort\n");
    return;
  }

  begin = clock();
  selectionSort(arr, len);
  end = clock();

  printf("selection exec time: %f\n", execTime(begin, end));
}

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    printf("missing args\n");
    return 1;
  }

  else if (argc > 2) {
    printf("too many args\n");
    return 1;
  }

  int numItems = atoi(argv[1]);

  FILE *file = fopen("data.txt", "r");

  int items[numItems];

  /* parse the text file */
  for (i = 0; i < numItems; i++) {
    fscanf(file, "%d", &items[i]);
  }

  int *mergeSortItems = cpyArr(items, numItems);
  int *radixSortItems = cpyArr(items, numItems);
  int *selectionSortItems = cpyArr(items, numItems);

  free(items);

  mergeSortTest(mergeSortItems, 0, numItems);
  free(mergeSortItems);

  radixSortTest(radixSortItems, numItems);
  free(radixSortItems);

  selectionSortTest(selectionSortItems, numItems);
  free(selectionSortItems);

  return 0;
}
