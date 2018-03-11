#ifndef PROJECT_2_H
#define PROJECT_2_H
using namespace std;

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <regex>
#include "./projlex.h"
using namespace std;

class Lex {
public:
  static void Parse(istream* in) {
    int lineNumber = -1;
    char c;

    getNextToken(in, &lineNumber);
  } 
};

// map<TType, string> TokenNames = {
//   { SET,    "set" },
//   { PRINT,  "print" },
//   { VAR,    "var" },
//   { REPEAT, "repeat" },
//   { ICONST, "iconst" },
//   { SCONST, "sconst" },
//   { PLUS,   "plus" },
//   { MINUS,  "minus" },
//   { STAR,   "star" },
//   { COLON,  "colon" },
//   { LSQ,    "lsq" },
//   { RSQ,    "rsq" },
//   { LPAREN, "lparen" },
//   { RPAREN, "rparen" },
//   { SC,     "sc" },
//   { RPAREN, "rparen" },
//   { ERR,    "err" },
//   { DONE,   "done" }
// };

// map<TType, bool> TokenBools = {
//   { IDENT,  true },
//   { SCONST, true },
//   { ICONST, true },
//   { ERR,    true },
// };

// returns true if the flag provided is found
extern bool inSet(const set<string> flags, string arg) {
  for(auto flag : flags)
    if(flag == arg)
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

set<TType> valid_output_tokens = { IDENT, SCONST, ICONST, ERR };

// custom output operator
extern ostream& operator << (ostream& out, const Token& tok) {
  out << tok.GetTokenType();

  if(inSet(valid_output_tokens, tok.GetTokenType()))
    out << "(" << tok.GetLexeme() << ")";

  return out;
}

// finds and returns the next token
extern Token getNextToken(istream* in, int* linenum) {
  char c;
  string lexeme;

  // used to manage what state we are in when lexing
  enum LexState {
    BEGIN,    // begin 'state'
    // INKEY,    // found a keyword 'state'
    INID,     // found an identifier 'state'
    INSTR,    // found a string 'state'
    ININT,    // found an int 'state'
    INCOM     // found a comment 'state'
  } state = BEGIN;

  // loop through the characters in the stream
  while(in->get(c)) {
    switch(state) {
      // find the first char in our lexeme
      case BEGIN:
        // increment linenum
        if(c == '\n')
          ++linenum;

        // ignore whitespace
        if(isspace(c))
          continue;

        lexeme = c;

        // found char(s)
        if(isalpha(c)) {
          state = INID;
          continue;
        }

        // found digit
        if(isdigit(c) || (c == '-' && isdigit(in->peek())) ) {
          state = ININT;
          continue;
        }

        // found a comment
        if(c == '/' && in->peek() == '/') {
          state = ININT;
          continue;
        }

        // found a string
        if(c == '"') {
          state = INSTR;
          continue;
        }

        // cases for the first character found in the lexeme
        switch(c) {
          case '+':
            return Token(PLUS, lexeme, *linenum);

          case '-':
            return Token(MINUS, lexeme, *linenum);

          case '*':
            return Token(STAR, lexeme, *linenum);

          case ':':
            return Token(COLON, lexeme, *linenum);

          case '[':
            return Token(LSQ, lexeme, *linenum);

          case ']':
            return Token(RSQ, lexeme, *linenum);

          case '(':
            return Token(LPAREN, lexeme, *linenum);

          case ')':
            return Token(RPAREN, lexeme, *linenum);

          case ';':
            return Token(SC, lexeme, *linenum);
        }

        // else returns an error
        return Token();
        break;

      // handles the idenitifier/keyword found
      case INID:
        if(isalpha(c)) {
          lexeme += c;
          continue;
        }

        in->putback(c);

        // find if the IDENT is actually a reserved keyword
        if(lexeme == "set")
          return Token(SET, lexeme, *linenum);

        if(lexeme == "print")
          return Token(PRINT, lexeme, *linenum);

        if(lexeme == "var")
          return Token(VAR, lexeme, *linenum);

        if(lexeme == "repeat")
          return Token(REPEAT, lexeme, *linenum);

        // else return the IDENT found
        return Token(IDENT, lexeme, *linenum);

      // handles the int found
      case ININT:
        if(isdigit(c)) {
          lexeme += c;
          continue;
        }

        in->putback(c);
        return Token(ICONST, lexeme, *linenum);

      // handles the string found
      case INSTR:
        if(c == '\n')
          return Token();

        lexeme += c;
        if(c != '"')
          continue;

        return Token(SCONST, lexeme, *linenum);

      // handles the comment found
      case INCOM:
      if(c != '\n')
        continue;

      state = BEGIN;
      break;

      default:
        cout << "Something went horribly wrong :(" << endl;
        return Token();
    }
  }

  if(state == BEGIN)
    return Token(DONE, "", *linenum);

  else if(state == INID)
    return Token(IDENT, lexeme, *linenum);

  else if(state == ININT)
    return Token(ICONST, lexeme, *linenum);

  else
    return Token();
}

#endif 
