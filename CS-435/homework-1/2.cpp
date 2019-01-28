#include <iostream>
using namespace std;

int getMax(int arr[], int len) {
  int max = arr[0];

  for (int i = 0; i < len; i++) {
    if (arr[i] > i)
      max = arr[i];
  }

  return max;
}

// question 2
int main(int argc, char const *argv[]) {
  int arr[] = {10, 20, 30, 40, 100, 200};
  int len = sizeof(arr) / sizeof(int);

  cout << getMax(arr, len) << endl;

  return 0;
}
