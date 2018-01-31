#include <iostream>
using namespace std;

int main() {
  auto sayHello = []() {
    cout << "Hello World";
  };

  sayHello();
  
  return 0;
}
