#include <iostream>
#include <fstream> // file streams
#include <cmath> // abs, sqrt, pow
#include <string>
#include <vector> // vector<TYPE> var
using namespace std;

// template for the abstract data type 'MATRIX'
struct MATRIX {
  string name;
  double arr[2][2];
  // 2x2 matrix
  // [a b]
  // [c d]
};

void createMatrix(vector<MATRIX>&);

int main() {
  vector<MATRIX> matrices;

  return 0;
}

void createMatrix(vector<MATRIX>& matrix) {
  MATRIX m;

  cout << "Enter the name for the matrix: "; 
}
