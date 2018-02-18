#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

int main() {
  stringstream ss("Hello Wolrd");
  string tmp;

  while(ss >> tmp) {
    if(!ss.eof())
      cout << tmp;
    else if(ss.eof())
      cout << " WORLD";
  }
}
