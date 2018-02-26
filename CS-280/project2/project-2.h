#ifndef LEXER_H
#define LEXER_H
using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include "./projlex.h"
using namespace std;

class Lexer {
public:
  Lexer() {
    foo();
  }

  static void foo() {
    Token myToken;
    cout << myToken.GetTokenType() << endl;
    cout << myToken.GetLexeme() << endl;
    cout << myToken.GetLinenum() << endl;
  }
};

// returns true if the flag provided is found
extern bool inFlags(const set<string> flags, string arg) {
  for(auto flag : flags)
    if(flag == arg)
      return true;
  return false;
}

#endif 
