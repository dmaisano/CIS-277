#ifndef radix_h
#define radix_h

#include <stdio.h>
#include <stdlib.h>

int i;

int getMax(int *arr, int len) {
  int max = arr[0];

  for (i = 1; i < len; i++)
    if (arr[i] > max)
      max = arr[i];

  return max;
}

void countSort(int *arr, int len, int exp) {
  int output[len];
  int count[10] = {0};

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

void radixSort(int *arr, int len) {
  int max = getMax(arr, len);

  int exp;
  for (exp = 1; max / exp > 0; exp *= 10)
    countSort(arr, len, exp);
}

#endif
