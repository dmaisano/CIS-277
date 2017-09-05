#include <iostream>
using namespace std;

void getArray(double*, int); // double[] == double*
void printArray(double*,int);

int main() {
  int size = 5;
  double nums[size];

  getArray(nums, size);
  printArray(nums, size);
  
  return 0;
}

void getArray(double* arr, int size) {
  for(int i = 0; i < size; i++) {
    cout << "Enter a number for element " << i << ": ";
    cin >> arr[i];
  }
}

void printArray(double* arr, int size) {
  for(int i = 0; i < size; i++) {
    cout << "Element: " << i << "\tValue: " << arr[i] << "\n";
  }
}
