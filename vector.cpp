#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector <int> nums;
  int num;
  int size;
  
  cout << "Enter the size of the vector: ";
  cin >> size;

  for(int i = 0; i < size; i++) {
    cout << "Enter element " << i << ": ";
    cin >> num;
    nums.push_back(num);
  }

  for(int i = 0; i < size; i++) {
    cout << "Element " << i  << ": " << nums[i] << "\n";
  }
  
  return 0;
}
