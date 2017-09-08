#include <iostream>
using namespace std;

int main() {
  int nums[] = {1, 2, 3, 4, 5};

  int size = sizeof(nums) / sizeof(nums[0]);

  cout << "Size: " << size << "\n\n";
  
  return 0;
}
