#include <iostream>
using namespace std;

int main() {
  int *arr, size;

  cout << "Enter size of the array: ";
  cin >> size;

  arr = new int[size];

  for(int i = 1; i <= size; i++) {
    if(i % 2 == 0) {
      arr[i] = NULL;
    }

    else {
      arr[i] = i;
    }

    cout << "Item: " << arr[i] << "\n";
  }

  cout << "\n";
  
  
  return 0;
}
