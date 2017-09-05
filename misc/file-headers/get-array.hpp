#include <iostream>
using namespace std;

void getArray(double* arr, int size) {
  for(int i = 0; i < size; i++) {
    cout << "Enter a number for element " << i << ": ";
    cin >> arr[i];
  }
}
