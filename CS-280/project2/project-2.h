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
  Lexer(const string fileName) {
    ifstream file(fileName);
    string fileString, currentLine;
    char c;

    // loop through the entire file, one char at a time
    while(file.get(c)) {
      currentLine += c;
      if(c == '\n') {
        fileString += (currentLine + '\n');
        // reinitalizes the current line to an empty string
        currentLine = "";
      }
    }


  }
};

// returns true if the flag provided is found
extern bool inFlags(const set<string> flags, string arg) {
  for(auto flag : flags)
    if(flag == arg)
      return true;
  return false;
}

// finds and returns the Token Obj 
extern Token getNextToken(istream *in, int *linenum) {

}

#endif 
