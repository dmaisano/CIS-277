#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval begin, end;

// get max value in arr
int getMax(int *arr, int n) {
  int max = arr[0];

  for (int i = 1; i < n; i++)
    if (arr[i] > max)
      max = arr[i];

  return max;
}

// counting sort function
void countSort(int arr[], int n, int exp) {
  // array that will be returned
  int output[n];
  int i, count[10] = {0};

  // Store count of occurrences in count[]
  for (i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  // Change count[i] so that count[i] now contains actual
  //  position of this digit in output[]
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  // Copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < n; i++)
    arr[i] = output[i];
}

void radixSort(int arr[], int n) {
  // Find the maximum number to know number of digits
  int m = getMax(arr, n);

  // Do counting sort for every digit. Note that instead
  // of passing digit number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; m / exp > 0; exp *= 10)
    countSort(arr, n, exp);
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

  FILE *dataFile = fopen("data.txt", "r");

  int *items = calloc(numItems, sizeof(int));

  int i;

  // parse the text file
  for (i = 0; i < numItems; i++) {
    fscanf(dataFile, "%d", &items[i]);
  }

  fclose(dataFile);

  gettimeofday(&begin, NULL);
  radixSort(items, numItems);
  gettimeofday(&end, NULL);

  unsigned long execTime = end.tv_usec - begin.tv_usec;

  FILE *results = fopen("results.txt", "ab+");

  fprintf(results, "radix [%d items] (%lums)\n", numItems, execTime);

  fclose(results);

  return 0;
}
