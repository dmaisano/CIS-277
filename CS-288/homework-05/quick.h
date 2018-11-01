#ifndef quick_h
#define quick_h

#include <stdio.h>
#include <stdlib.h>

void quickSwap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {

    if (arr[j] <= pivot) {
      i++;
      quickSwap(&arr[i], &arr[j]);
    }
  }
  quickSwap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quickSort(int *arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);

    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

#endif
