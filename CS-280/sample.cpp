#include <iostream>
using namespace std;

int main() {
  int* x;

  *x = 10;

  cout << *x << '\n' << x;

  return 0;
}
