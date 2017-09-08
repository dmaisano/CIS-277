#include <iostream>
#include <vector> // vector
#include <fstream> // file streams
#include <string>
#include <sstream> // stringstream
#include <vector>
#include "struct.hpp"
using namespace std;

void menu();

VECTOR calc_sum(VECTOR, VECTOR); // adds the values of two VECTOR types
//VECTOR print_vector(VECTOR); // function to print contents of vector to file

int main() {

  cout << "\n";
  return 0;
}

VECTOR calc_sum(VECTOR vector1, VECTOR vector2) {
  VECTOR v;

  cout << "Enter the new name for the sum of the vectors: ";
  cin >> v.name;

  v.x = (vector1.x + vector2.x);

  v.y = (vector2.y + vector2.y);

  return v;
}
