/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 11
Due by 8/10/17
*/

#include <iostream>
using namespace std;

int main() {
  int userValues[10];

  for (int i = 0; i < 10; i++) {
    cout << "Enter value " << i + 1 << ": ";
    cin >> userValues[i];
  }

  int largest = userValues[0];

  for (int j = 0; j < 10; j++) {
    if (userValues[j] > largest) {
      largest = userValues[j];
    }
  }

  int smallest = userValues[0];

  for (int k = 0; k < 10; k++) {
    if (userValues[k] < smallest) {
      smallest = userValues[k];
    }
  }

  cout << "\nLargest value: " << largest << "\nSmallest value: " << smallest;

  return 0;
}
