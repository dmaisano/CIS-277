#include <iostream>
#include <vector> // vector
#include <fstream> // file streams
#include <string>
#include <sstream> // stringstream/istringstream
#include <stdlib.h> // strtod
#include <vector>
#include "struct.hpp"
using namespace std;

int main()
{
  vector<VECTOR> vect;
  VECTOR v;
  string input = "vect1,10,5";
  istringstream ss(input);

  for(int i = 0; i < 3; i++) {
    string item;
    getline(ss, item, ',');

    if(i == 0) {
      v.name = item;
    }
    else if(i == 1) {
      istringstream(item) >> v.x;
    }
    else if(i == 2) {
      istringstream(item) >> v.y;
      vect.push_back(v);
    }
  }

  for(int i = 0; i < vect.size(); i++) {
    cout << vect[i].name << ": ( " << vect[i].x << ", " << vect[i].y << " )\n";
  }

  cout << "\n";
  
  return 0;
}
