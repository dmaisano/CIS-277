#include <iostream>
#include <vector> // vector
#include <fstream> // file streams
#include <string>
#include <sstream> // stringstream
#include <vector>
#include "group/two-dim-vector/struct.hpp"
using namespace std;

void splitVectorData(vector<VECTOR>&, string);
void splitScalarData(vector<SCALAR>&, string);

int main() {
  vector<VECTOR> vect;
  string input = "vect1,10.20,5.54";

  splitVectorData(vect, input);

  for(int i = 0; i < vect.size(); i++) {
    cout << vect[i].name << ": ( " << vect[i].x << ", " << vect[i].y << " )\n";
  }

  cout << "\n";
  
  return 0;
}

void splitVectorData(vector<VECTOR>& vect, string line) {
  VECTOR v;
  istringstream ss(line);

  for(int i = 0; i < 3; i++) {
    string item;
    getline(ss, item, ',');

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
