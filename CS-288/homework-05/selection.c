#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timeval begin, end;

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void selectionSort(int *arr, int n) {
  int i, j, min_idx;

  // One by one move boundary of unsorted subarray
  for (i = 0; i < n - 1; i++) {
    // Find the minimum element in unsorted array
    min_idx = i;
    for (j = i + 1; j < n; j++)
      if (arr[j] < arr[min_idx])
        min_idx = j;

    // Swap the found minimum element with the first element
    swap(&arr[min_idx], &arr[i]);
  }
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

  int numItems = atol(argv[1]);

  if (numItems >= 1000000) {
    printf("skipping selection sort for %d items\n", numItems);
    return 0;
  }

  FILE *dataFile = fopen("data.txt", "r");

  int *items = calloc(numItems, sizeof(int));

  int i;

  // parse the text file
  for (i = 0; i < numItems; i++) {
    fscanf(dataFile, "%d", &items[i]);
  }

  fclose(dataFile);

  gettimeofday(&begin, NULL);
  selectionSort(items, numItems);
  gettimeofday(&end, NULL);

  unsigned long execTime = end.tv_usec - begin.tv_usec;

  FILE *results = fopen("results.txt", "ab+");

  fprintf(results, "selection [%d items] (%lums)\n", numItems, execTime);

  fclose(results);

  return 0;
}
