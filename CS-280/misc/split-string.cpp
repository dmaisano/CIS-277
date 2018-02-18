#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <map>
#include <vector>
using namespace std;

vector<string> squish(string line) {
  vector<string> res; // result to be returned
  istringstream ss(line);
  string item;

  // iterates over each word per line
  while(ss >> item) {
    cout << item; continue;
    string tmp = "";
    bool foundChar = false;

    // iterates over each character per word
    for(auto c : item) {
      // executes if any non-whitespace char is found
      if(!isspace(c)) {
        tmp += c;
        foundChar = true;
      }

      // executes if any whitespace is found after the word/char
      if(isspace(c) && foundChar)
        break;
    }

    res.push_back(tmp);
  }

  return res;
}

vector<vector<string>> parse(const string fileName, string flag) {
  // continues if file exists, if not exits program
  if(ifstream(fileName))
    ; else exit(0);

  vector<vector<string>> res; // contains list of all lines with their words
  ifstream file(fileName); // file
  string line = ""; // current line

  // since nothing is copied there is no need to iterate over the file
  if(flag == "-q")
    return res;

  // iterate over each line in the file
  while(getline(file, line)) {
    if(flag == "-s") {
      auto words = squish(line);

      res.push_back(words);
    }
  }

  return res;
}

int main() {
  string fileName = "../project1/p1cases/third.txt";

  // vector<vector<string>> temp = {
  //   {"hello"},
  //   {"jello"},
  //   {"yello"}
  // };

  auto res = parse(fileName, "-s");

  for(auto line : res) {
    for(auto word : line) {
      cout << word << " ";
    }
      
    cout << endl;
  }
}
