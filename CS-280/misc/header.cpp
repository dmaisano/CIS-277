#include <iostream>
#include "./header.h"
using namespace std;

int main() {
  Dog bork;

  cout << bork.getName() << " is a " << bork.getBreed() << " who is " << bork.getAge() <<  " years old";
}
