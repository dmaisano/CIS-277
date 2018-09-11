#include <cctype>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> squish(string line) {
  istringstream ss(line);
  string item, squishedLine;

  // iterates over each word per line
  while (ss >> item) {
    cout << item; // continue;
    string tmp = "";
    bool foundChar = false;

    // iterates over each character per word
    for (auto c : item) {
      // executes if any non-whitespace char is found
      if (!isspace(c)) {
        tmp += c;
        foundChar = true;
      }

      // executes if any whitespace is found after the word/char
      if (isspace(c) && foundChar)
        break;
    }
  }

  return squishedLine;
}

string parse(const string fileName, string flag) {
  // continues if file exists, if not exits program
  if (ifstream(fileName).fail())
    exit(0);

  string res, curLine;
  ifstream file(fileName);

  // since nothing is copied there is no need to iterate over the file
  if (flag == "-q")
    return res;

  // iterate over each line in the file
  while (getline(file, curLine)) {
    if (flag == "-s") {
      auto words = squish(curLine);
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

  for (auto line : res) {
    for (auto word : line) {
      cout << word << " ";
    }

    cout << endl;
  }
}
