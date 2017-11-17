#include <iostream>
using namespace std;

void countDown(int);

int main() {
  countDown(10);
  
  return 0;
}

void countDown(int n) {
  cout << n << "\n";

  if(n == 0)
    return;

  countDown(n-1);
}
