#include <iostream>
#include <vector>
#include "struct.hpp"
#include "file.hpp"
#include "operations.hpp"
using namespace std;

void menu();

int main() {
  menu();
  
  return 0;
}

void menu() {
  vector<VECTOR> vect;
  getVectors(vect);
  int size = vect.size();
  int menuChoice = -99;

  if(vect.size() > 0) {
    cout << "Size: " << vect.size() << "\n\n";
  }
  
  while(menuChoice != -1) {

    if(size > 0) {
      cout << "Enter 0 to display vectors.\n";
    }

    cout << "Enter 1 to create a new vector.\n";
    
    if(size > 0) {
      cout << "Enter 2 to delete a vector.\n";
      cout << "Enter 3 perform an operation on a vector.\n";
    }

    cout << "Enter an option: ";
    cin >> menuChoice;

    cout << "\n";

    if(menuChoice == -1) { // exit
      writeVector(vect);
      continue;
    }

    else if(menuChoice == 0 && size > 0) // print vectors to console
      printVector(vect);
    
    else if(menuChoice == 1 && size > 0);
      // create vector

    else if(menuChoice == 2 && size > 0);
      // delete a vector
    
    else if(menuChoice == 3 && size > 0);
      performOperation(vect);

  }
}
