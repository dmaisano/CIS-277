#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> vect;
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
  }
  
  return 0;
}
