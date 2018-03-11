#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <map>
#include <set>
#include "./token.h"
using namespace std;

// returns true if the flag provided is found
extern bool inSet(const set<string> flags, string arg) {
  for(auto flag : flags)
    if(arg == flag)
      return true;
  return false;
}

// overloaded for TTypes
extern bool inSet(const set<TType> types, TType arg) {
  for(auto type : types)
    if(arg == type)
      return true;
  return false;
}

// lexical analyzer class 
class Lex {
public:
  static void Lexer(istream* in, const set<string> flags) {
    
  }
};

#endif
