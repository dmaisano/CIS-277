#include <iostream>
#include <vector>
using namespace std;

void getVector(vector<int>&); // & = passed by reference
void doubleVector(vector<int>&, const vector<int>&); // the newVector is the first parameter, original is the second
void printVector(const vector<int>&); // const is used as the vector is not intended to change within the function

int main() {
  vector<int> list;
  vector<int> doubledList;

  getVector(list);

  doubleVector(doubledList, list);

  printVector(doubledList);
  
  return 0;
}

void getVector(vector<int>& vect) {
  int input = 0;
  int counter = 0;
  cout << "To exit enter '-1'\n";

  while(input != -1) {
    cout << "Enter a value for element " << counter << ": ";
    cin >> input;

    if(input == -1)
      break;
    
    else {
      vect.push_back(input);
      counter++;
    }
  }
}

void doubleVector(vector<int>& newVector, const vector<int>& vect) {
  for(int i = 0; i < vect.size(); i++) {
    newVector.push_back(vect[i] * 2);
  }
}

void printVector(const vector<int>& vect) {
  for(int i = 0; i < vect.size(); i++) {
    cout << "Element " << i << "\tValue: " << vect[i] << "\n";
  }
}
