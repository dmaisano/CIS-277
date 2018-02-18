#include <iostream>
#include <string>
using namespace std;

int main() {
  bool *foo = new bool;
  bool *bar = new bool;
  *foo = false;
  *bar = false;

  cout << *foo;
  delete foo, bar;
}
