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

Token getNextToken(istream* in, int* linenum) {
  // used to manage what state we are in when lexing
  enum LexState {
    BEGIN,          // begin 'state'
    foundINDENT,    // found an identifier 'state'
    foundSTR,       // found a string 'state'
    foundINT,       // found an int 'state'
    foundCOMMENT    // found a comment 'state'
  } state = BEGIN;  // set the initial state to BEGIN

  string lexeme;
  char c;
  int count = 0;

  while(in->get(c)) {
    // manage each
    switch(state) {
      case BEGIN:
        // 
        if(c == '\n') {
          ++*linenum;
          continue;
        }

        if(isspace(c))
          continue;

        // assign the initial char of the lexeme
        lexeme = c;

        if(isalpha(c)) {
          state = foundINDENT;
          continue;
        }

      // handle the IDENT found
      case foundINDENT:
        if(isalpha(c)) {
          lexeme += c;
          // cout << lexeme << endl;
          continue;
        }

        else if(!isalpha(c)) {
          in->putback(c); // return the non-alpha char back to the strea

          // determine if the IDENT is actually a reserved keyword
          if(lexeme == "set")
            return Token(SET, lexeme, *linenum);

          if(lexeme == "print")
            return Token(PRINT, lexeme, *linenum);

          if(lexeme == "var")
            return Token(VAR, lexeme, *linenum);

          if(lexeme == "repeat")
            return Token(REPEAT, lexeme, *linenum);
          
          // returns the IDENT found if not matches found
          return Token(IDENT, lexeme, *linenum);
        }
    }
  }

  if(state == BEGIN)
    return Token(DONE, lexeme, *linenum);

  return Token(ERR, lexeme, *linenum);
}

vector<Token> getAllTokens(istream* in, int* linenum) {
  vector<Token> tokens;
  Token t;

  while((t = getNextToken(in, linenum)).GetTokenType() != DONE && t.GetTokenType() != ERR)
    tokens.push_back(t);

  return tokens;
}

// lexical analyzer class 
class Lex {
public:
  static void Lexer(istream* in, const set<string> flags) {
    int linenum = 1;
    auto tokens = getAllTokens(in, &linenum);

    for(auto token : tokens) {
      cout << "line num: " << token.GetLinenum();
      cout << "\ttype: " << token.GetTokenType();
      cout << "\t\tlexeme: " << token.GetLexeme() << endl;
    }
  }
};

#endif
