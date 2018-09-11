#include <iostream>
using namespace std;

int *doubledArray(int[], int);

int main() {
  int n = 4;
  int(*list) = new int[n]{0, 1, 2, 3};
  auto newList = doubledArray(list, n);

  for (int i = 0; i < n * 2; i++)
    cout << newList[i] << endl;

  return 0;
}

int *doubledArray(int *list, int size) {
  int newSize = size * 2;
  int *newList = new int[newSize];

  for (int i = 0; i < newSize; i++) {
    if (i < size)
      newList[i] = list[i];

    else
      newList[i] = 0;
  }

  return newList;
}
