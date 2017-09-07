#include <iostream>
#include <vector> // vector
#include <fstream> // file streams
#include <string>
#include <sstream> // stringstream
#include <vector>
#include "struct.hpp"
using namespace std;

void writeVectorData(const vector<VECTOR>&);
void getVectorData(vector<VECTOR>&);
void splitVectorData(vector<VECTOR>&, string);
void printVector(const vector<VECTOR>&);

void writeScalarData(const vector<SCALAR>&);
void getScalarData(vector<SCALAR>&);
void splitScalarData(vector<SCALAR>&, string);
void printScalar(const vector<SCALAR>&);

int main() {
  vector<VECTOR> vect;

  getVectorData(vect);
  printVector(vect);

  cout << "\n";
  
  return 0;
}

void getVectorData(vector<VECTOR>& vect) {
  string currentLine;
  ifstream dataFile("vector.dat");

  while(getline(dataFile, currentLine)) {
    splitVectorData(vect, currentLine);
  }

  dataFile.close(); // close file when done
}

void splitVectorData(vector<VECTOR>& vect, string line) {
  VECTOR v;
  istringstream ss(line);

  for(int i = 0; i < 3; i++) {
    string item;
    getline(ss, item, ',');

    if(item == "") // ignores a line if empty
      continue;

    if(i == 0)
      v.name = item;

    else if(i == 1)
      istringstream(item) >> v.x;
      
    else if(i == 2) {
      istringstream(item) >> v.y;
      vect.push_back(v);
    }
  }
}

void writeVectorData(const vector<VECTOR>& vect) {
  ofstream dataFile("vector.dat", ios::app); // creates file if none exists, appends to end of file if exists
  // int size = vect.size();

  for(int i = 0; i < vect.size(); i++) {
    dataFile << vect[i].name << "\t" << vect[i].x << "\t" << vect[i].y << "\n";
  }

  dataFile.close(); // close file when done
}

void printVector(const vector<VECTOR>& vect) {
  for(int i = 0; i < vect.size(); i++) {
    cout << vect[i].name << ": ( " << vect[i].x << ", " << vect[i].y << " )\n";
  }
}

void splitScalarData(vector<SCALAR>& vect, string line) {
  SCALAR s;
  istringstream ss(line);

  for(int i = 0; i < 3; i++) {
    string item;
    getline(ss, item, ',');

    if(i == 0) {
      s.name = item;
    }

    else if(i == 1) {
      istringstream(item) >> s.product;
      vect.push_back(s);
    }
  }
}
