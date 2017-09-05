#include <iostream>
#include <vector>
#include <fstream>
#include "struct.hpp"
using namespace std;

void writeFile(const vector<VECTOR>&);

int main() {
  vector<VECTOR> myVectors;

  VECTOR vect1;
  vect1.name = "VECTOR 1";
  vect1.x = 10;
  vect1.y = 5;

  VECTOR vect2;
  vect2.name = "VECTOR 2";
  vect2.x = 7;
  vect2.y = 11;

  myVectors.push_back(vect1);
  myVectors.push_back(vect2);

  writeFile(myVectors);
  
  return 0;
}

void writeFile(const vector<VECTOR>& vect) {
  ofstream file; // file object
  file.open("file.dat", ios::app); // creates file if none exists, appends to end of file if exists
  int size = vect.size();
  
  for(int i = 0; i < size; i++) {
    file << "Name: " << vect[i].name << " - ( " << vect[i].x << ", " << vect[i].y << " )\n";
  }

  file.close();
}
