#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  // vector<string> temp = {"HELLO", "WORLD", "\0"};

  // for(auto word : temp) {
  //   if(word == "\0")
  //     cout << "NULL";
  //   else
  //     cout << word << " ";
  // }

  istringstream ss("hello  ");
  string word;

  ss >> word;
  int count = 0;

  for(auto c : word) {
    ++count;
  }

  cout << ss.str() << endl;

  cout << count;
}
