#include <iostream>
#include <vector> // vector
#include "struct.hpp"
#include "file.hpp"
using namespace std;

void calc_sum(vector<VECTOR>&, VECTOR, VECTOR); // adds the values of two VECTOR types

int main() {
  vector<VECTOR> vect;
  getVector(vect);

  calc_sum(vect, vect[0], vect[1]);
  
  return 0;
}

void calc_sum(vector<VECTOR>& vect, VECTOR vector1, VECTOR vector2) {
  VECTOR v;

  cout << "Enter the two vectors from the list you wish to add: ";
  printVector(vect);

  cout << "Enter the new name for the sum of the vectors: ";
  cin >> v.name;

  v.x = (vector1.x + vector2.x);

  v.y = (vector1.y + vector2.y);

  vect.push_back(v);
  writeVector(vect);
}
