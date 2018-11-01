#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t begin, end;

void selectSwap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void selectionSort(int *arr, int n) {
  int i, j, minIndex;

  for (i = 0; i < n - 1; i++) {

    minIndex = i;
    for (j = i + 1; j < n; j++)
      if (arr[j] < arr[minIndex])
        minIndex = j;

    selectSwap(&arr[minIndex], &arr[i]);
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

  int numItems = atoi(argv[1]);

  if (numItems > 1000000) {
    printf("skipping selection sort\n");
    return 0;
  }

  FILE *file = fopen("data.txt", "r");

  int items[numItems];

  /* parse the text file */
  int i;
  for (i = 0; i < numItems; i++) {
    fscanf(file, "%d", &items[i]);
  }

  fclose(file);

  clock_t begin = clock();
  selectionSort(items, numItems);
  clock_t end = clock();

  float execTime = (double)(end - begin) / CLOCKS_PER_SEC;

  FILE *results = fopen("results.txt", "ab+");
  fprintf(results, "selection sort (%d) took %fs\n", numItems, execTime);
  fclose(results);

  return 0;
}
