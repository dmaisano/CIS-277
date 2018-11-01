#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long i;
struct timeval start, stop;

void merge(long *arr, long l, long m, long r) {
  long i, j, k;
  long n1 = m - l + 1;
  long n2 = r - m;

  long L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(long *arr, long l, long r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

int main(long argc, char const *argv[]) {
  if (argc < 2) {
    printf("missing args\n");
    return 1;
  }

  else if (argc > 2) {
    printf("too many args\n");
    return 1;
  }

  long numItems = atol(argv[1]);

  FILE *file = fopen("data.txt", "r");

  long items[numItems];

  /* parse the text file */
  for (i = 0; i < numItems; i++) {
    fscanf(file, "%d", &items[i]);
  }

  fclose(file);

  gettimeofday(&start, NULL);
  mergeSort(items, 0, numItems);
  gettimeofday(&stop, NULL);

  long execTime = stop.tv_usec - start.tv_usec;

  FILE *results = fopen("results.txt", "ab+");
  fprintf(results, "merge sort (%lu) took %lus\n", numItems, execTime);
  fclose(results);

  return 0;
}
