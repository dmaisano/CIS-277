#ifndef radix_h
#define radix_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long i;
struct timeval start, stop;

long getMax(long *arr, long len) {
  long max = arr[0];

  for (i = 1; i < len; i++)
    if (arr[i] > max)
      max = arr[i];

  return max;
}

void countSort(long *arr, long len, long exp) {
  long output[len];
  long count[10] = {0};

  for (i = 0; i < len; i++)
    count[(arr[i] / exp) % 10]++;

  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (i = len - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  for (i = 0; i < len; i++)
    arr[i] = output[i];
}

void radixSort(long *arr, long len) {
  long max = getMax(arr, len);

  long exp;
  for (exp = 1; max / exp > 0; exp *= 10)
    countSort(arr, len, exp);
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

  long numItems = atol(argv[1]);

  FILE *file = fopen("data.txt", "r");

  long items[numItems];

  /* parse the text file */
  for (i = 0; i < numItems; i++) {
    fscanf(file, "%ld", &items[i]);
  }

  fclose(file);

  gettimeofday(&start, NULL);
  radixSort(items, numItems);
  gettimeofday(&stop, NULL);

  long execTime = stop.tv_usec - start.tv_usec;

  FILE *results = fopen("results.txt", "ab+");
  fprintf(results, "radix sort (%ld) took %lds\n", numItems, execTime);
  fclose(results);

  return 0;
}

#endif
