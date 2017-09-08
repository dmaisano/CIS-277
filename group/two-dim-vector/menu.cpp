#include <iostream>
#include <vector>
#include "struct.hpp"
#include "file.hpp"
using namespace std;

void menu();

int main() {
  menu();
  
  return 0;
}

void menu() {
  vector<VECTOR> vect;
  getVector(vect);
  int size = vect.size();
  int menuChoice = -99;

  if(vect.size() > 0) {
    cout << "Size: " << vect.size() << "\n\n";
  }
  
  while(menuChoice != -1) {

    if(vect.size() > 0) {
      cout << "Enter 0 to display vectors.\n";
    }

    cout << "Enter 1 to create a new vector.\n";
    cout << "Enter 2 to delete a vector.\n";
    cout << "Enter 3 to add two vectors.\n";
    cout << "Enter 4 to subtract two vectors.\n";
    cout << "Enter 5 to multiply a vector by a scalar.\n";
    cout << "Enter 6 to multiply two vectors.\n";
    cout << "Enter 7 to get the magnitude of a vector.\n";

    cin >> menuChoice;

    cout << "\n";

    if(menuChoice == -1) { // exit
      writeVector(vect);
      continue;
    }

    else if(menuChoice == 0 && size > 0) // print vectors to console
      printVector(vect);
    
    else if(menuChoice == 1);
      //

  }
}
