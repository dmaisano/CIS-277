#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <map>
#include <vector>
using namespace std;

vector<string> splitString(const string &str) {
  // regex spaces("\\s(.*)"); 
  stringstream ss(str);
  string item;

  vector<string> res;

  while(ss >> item) {
    string temp = "";
    bool foundChar = false;

    // loops over each character in 'item'
    for(auto c : item) {
      // executes if any non-whitespace char is found
      if(!isspace(c)) {
        temp += c;
        foundChar = true;
      }

      // executes if any whitespace is found after the word/char
      if(isspace(c) && foundChar)
        break;
    }

    // appends word to the list
    res.push_back(temp);
  }

  return res;
}

string squish(string s) {
  if(s == "") {
    cout << "NO STRING PROVIDED" << endl;
    return "";
  }
  
  string res = "";
  auto items = splitString(s);

  for(auto item :  items)
    res += item + " ";

  // removes the trailing space at the end of the string
  res.pop_back();
  return res;
}

void func(string fileName) {
  if(ifstream(fileName))
    ;

  // skips the current word in the iteration if true
  bool skip = false;

  ifstream file(fileName);
  string line = "";

  // each current line is a string
  while(getline(file, line)) {
    // iterate over each char in the line
    for(auto c : line) {
      // do something
    }
  }
}

int main() {
  func("./first.txt");
}
