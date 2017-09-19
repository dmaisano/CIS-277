#include <iostream>
#include "get-array.hpp"
#include "print-array.hpp"
using namespace std;

int main() {
  int size = 5;
  double nums[size];

  getArray(nums, size);
  printArray(nums, size);
  
  return 0;
}

