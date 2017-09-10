#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> nums;

  for(int i = 0; i < 11; i++) {
    nums.push_back(i);
  }

  for(int i = 0; i < nums.size(); i++) { // delete the odd numbered values from the vector
    if(nums[i] % 2 != 0) {
      nums.erase(nums.begin()+i);
    }
  }

  for(int i = 0; i < nums.size(); i++) {
    cout << "Element: " << i << "\tValue: " << nums[i] << "\n";
  }
  
  return 0;
}

// the syntax on how to delete a vector

// vectorName.erase( vectorName.begin() + elementNumber );

