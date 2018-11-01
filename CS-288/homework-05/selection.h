#ifndef selection_h
#define selection_h

#include <stdio.h>
#include <stdlib.h>

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

#endif
