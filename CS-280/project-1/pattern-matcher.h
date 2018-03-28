#ifndef PATTERN_MATCHER_H
#define PATTERN_MATCHER_H
using namespace std;

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <regex>
using namespace std;

class PatternMatcher {
public:
  static void Parse(istream* in) {
    char c;

    while(in->get(c))
      cout << c;
  }
};

// returns true if the flag provided is found
extern bool inFlags(const set<string> flags, string arg) {
  for(auto flag : flags)
    if(flag == arg)
      return true;
  return false;
}

// returns a vector of strings per line
extern vector<vector<string>> parseFile() {
  vector<vector<string>> parsedFile;

  return parsedFile;
}

#endif 
