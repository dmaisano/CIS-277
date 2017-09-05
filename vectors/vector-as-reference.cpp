#include <iostream>
#include <vector>
using namespace std;

vector<int> passByRef(vector<int>&); // parameter is a vector passed by reference

int main() {
  vector<int> nums; // vector declaration

  passByRef(nums);
  
  for(int i = 0; i < nums.size(); i++) {
    cout << "Element: " << i << "\tValue: " << nums[i] << "\n";
  }
  
  return 0;
}

vector<int> passByRef(vector<int>& vect) {
  unsigned int size;
  double input;

  cout << "Enter the size for the vector: ";
  cin >> size;

  for(unsigned int i = 0; i < size; i++) {
    cout << "Enter a number for element " << i << ": ";
    cin >> input;
    vect.push_back(input);
  }
}
