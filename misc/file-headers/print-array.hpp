#include <iostream>
using namespace std;

void printArray(double* arr, int size) {
  for(int i = 0; i < size; i++) {
    cout << "Element: " << i << "\tValue: " << arr[i] << "\n";
  }
}
