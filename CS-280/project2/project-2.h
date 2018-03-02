#ifndef LEXER_H
#define LEXER_H
using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include "./projlex.h"
using namespace std;

class Lexer {
public:
  // lexical analyzer program
  Lexer(const string fileName = "") {
    vector<vector<Token>> tokenList;
    ifstream file(fileName);
    string fileString;
  }

private:
  vector<Token> getTokens(const string str) {
    
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

// finds and returns the Token Obj 
extern Token getNextToken(istream *in, int *linenum) {

}

extern int getUniqueTokens(vector<Token> tokens) {
  set<Token> uniqueTokens;

  // inserts unique values into a set
  for(auto token : tokens)
    uniqueTokens.insert(token);

  return uniqueTokens.size();
}

#endif 
