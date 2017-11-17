#include <iostream>
using namespace std;

int char_to_num(char);

int main() {
  char x = char_to_num('c');

  cout << "Value: " << x << "\n";
  
  return 0;
}

int char_to_num(char c) {
  return c-'a';
};
