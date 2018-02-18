#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<string> temp = {"HELLO", "WORLD", "\0"};

  for(auto word : temp) {
    if(word == "\0")
      cout << "NULL";
    else
      cout << word << " ";
  }
}
