#include <iostream>
#include <vector> // vector
#include <fstream> // file streams
#include <string>
#include <sstream> // stringstream
#include <vector>
#include "struct.hpp"
using namespace std;

void getVector(vector<VECTOR>&);
void splitVector(vector<VECTOR>&, string);
void writeVector(const vector<VECTOR>&);
void printVector(const vector<VECTOR>&);

void getScalar(vector<SCALAR>&);
void splitScalar(vector<SCALAR>&, string);
void writeScalar(const vector<SCALAR>&);
void printScalar(const vector<SCALAR>&);

int main() {
  vector<VECTOR> vect;

  getVector(vect);
  printVector(vect);
  writeVector(vect);

  cout << "\n";
  
  return 0;
}

void getVector(vector<VECTOR>& vect) {
  string currentLine;
  ifstream dataFile("vector.dat");

  while(getline(dataFile, currentLine)) {
    splitVector(vect, currentLine);
  }

  dataFile.close(); // close file when done
}

void splitVector(vector<VECTOR>& vect, string line) {
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

void writeVector(const vector<VECTOR>& vect) {
  ofstream dataFile("vector.dat", ios::out | ios::trunc);

  for(int i = 0; i < vect.size(); i++) {
    dataFile << vect[i].name << "," << vect[i].x << "," << vect[i].y;

    if(i != (vect.size() - 1)) { // prevents empty lines from being added to file
      dataFile << "\n";
    }
  }

  dataFile.close(); // close file when done
}

void printVector(const vector<VECTOR>& vect) {
  cout << "Vector Name: ( x, y )\n\n"; 

  for(int i = 0; i < vect.size(); i++) {
    cout << vect[i].name << ": ( " << vect[i].x << ", " << vect[i].y << " )\n";
  }

  cout << endl;
}

// void getScalar(const vector<SCALAR>&);

void splitScalar(vector<SCALAR>& vect, string line) {
  SCALAR s;
  istringstream ss(line);

  for(int i = 0; i < 2; i++) {
    string item;
    getline(ss, item, ',');

    if(item == "") // ignores a line if empty
    continue;

    if(i == 0) {
      s.name = item;
    }

    else if(i == 1) {
      istringstream(item) >> s.product;
      vect.push_back(s);
    }
  }
}
