#include <iostream>
#include <vector>
using namespace std;

vector<int> get_vector();

int main() {
  vector<int> nums;

  nums = get_vector();

  for(unsigned int i = 0; i < nums.size(); i++) {
    cout << "Element: " << i << "\tValue: " << nums[i] << "\n";
  }
  
  return 0;
}

vector<int> get_vector() {
  unsigned int size;
  double input;
  vector<int> vect;

  cout << "Enter the size for the vector: ";
  cin >> size;

  for(unsigned int i = 0; i < size; i++) {
    cout << "Enter a number for element " << i << ": ";
    cin >> input;
    vect.push_back(input);
  }

  return vect;
}
