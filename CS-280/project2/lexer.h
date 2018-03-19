#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <map>
#include <set>
#include <tuple>
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

// returns a Token
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

  while(in->get(c)) {
    // increment the linenumber
    if(c == '\n')
      (*linenum)++;

    // manage each state
    switch(state) {
      case BEGIN:
        
        if(c == '\n')
          continue;

        // ignore WS
        if(isspace(c))
          continue;

        // assign the initial char of the lexeme
        lexeme = c;

        if(isalpha(c)) {
          state = foundINDENT;
          continue;
        }

        if(isdigit(c)) {
          state = foundINT;
          continue;
        }

        // finds negtive integers
        if(c == '-' && isdigit(in->peek())) {
          state = foundINT;
          continue;
        }

        if(c == '#') {
          state = foundCOMMENT;
          continue;
        }

        if(c == '"') {
          state = foundSTR;
          continue;
        }
        
        // determine if the char is a valid operator
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

          // catches any weird IDENTS such as commas or apostrophes
          default:
            continue;
        }

      // handle the IDENT found
      case foundINDENT:
        if(isalpha(c) || isdigit(c)) {
          lexeme += c;
          continue;
        }

        else if(!isalpha(c) || !isdigit(c)) {
          if(c != '\n')
            in->putback(c);

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

      case foundSTR:
        if(c == '\n')
          return Token(ERR, lexeme, *linenum);

        if(c != '"') {
          lexeme += c;
          continue;
        }

        // if the end of the string is found
        if(c == '"')
          return Token(SCONST, lexeme, *linenum);

      case foundINT:
        if(isdigit(c)) {
          lexeme += c;
          continue;
        }

        // error detection
        if(isalpha(c)) {
          lexeme += c;
          return Token(ERR, lexeme, *linenum);
        }

        if(!isalpha(c) && !isdigit(c)) {
          if(c != '\n')
            in->putback(c);
          return Token(ICONST, lexeme, *linenum);
        }

        if(isspace(c)) {
          return Token(ICONST, lexeme, *linenum);
        }

      case foundCOMMENT:
        if(c != '\n')
          continue;

        if(c == '\n') {
          state = BEGIN;
          break;
        }
    }
  }

  if(in->eof())
    return Token(DONE, "", *linenum);

  if(state == BEGIN)
    return Token(DONE, lexeme, *linenum);

  return Token(ERR, "something went horribly wrong", *linenum);
}

// lexical analyzer class
class Lex {
public:
  static void Lexer(istream* in, const set<string> flags) {
    int linenum = 0;
    auto tokens = getAllTokens(in, &linenum, flags);

    if(inSet(flags, "-v"))
      verboseMode(tokens, flags);

    if(inSet(flags, "-mci"))
      mciMode(tokens);

    if(inSet(flags, "-sum"))
      sumMode(in, tokens);
  }

  // parse the file and find all tokens
  static vector<Token> getAllTokens(istream* in, int* linenum, const set<string> flags = {}) {
    vector<Token> tokens;
    Token t;

    while((t = getNextToken(in, linenum)).GetTokenType() != DONE) {
      tokens.push_back(t);

      if(t.GetTokenType() == ERR) {
        // raise an error by default if not in verbose mode
        if(!inSet(flags, "-v"))
          errorHandler(t);
        break;
      }
    }

    return tokens;
  }

  // outputs the token error
  static void errorHandler(Token tok) {
    cout << "Error on line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")" << endl;
  }

  // print stats using verbose mode
  static void verboseMode(vector<Token> tokens, const set<string> flags) {
    for(auto token : tokens) {
      auto tok = token.GetLexeme();
      auto toktype = token.GetTokenType();

      // removes the quotes from the SCONST
      if(toktype == SCONST) {
        tok.erase(0, 1);
        tok.pop_back();
      }

      switch(toktype) {
        case IDENT:
          cout << "IDENT(" << tok << ")" << endl; continue;
        case ICONST:
          cout << "ICONST(" << tok << ")" << endl; continue;
        case SCONST:
          cout << "SCONST(" << tok << ")" << endl; continue;
        case SET:
          cout << "SET" << endl; continue;
        case VAR:
          cout << "VAR" << endl; continue;
        case PRINT:
          cout << "PRINT" << endl; continue;
        case REPEAT:
          cout << "REPEAT" << endl; continue;
        case PLUS:
          cout << "PLUS" << endl; continue;
        case MINUS:
          cout << "MINUS" << endl; continue;
        case STAR:
          cout << "STAR" << endl; continue;
        case COLON:
          cout << "COLON" << endl; continue;
        case LSQ:
          cout << "LSQ" << endl; continue;
        case RSQ:
          cout << "RSQ" << endl; continue;
        case LPAREN:
          cout << "LPAREN" << endl; continue;
        case RPAREN:
          cout << "RPAREN" << endl; continue;
        case SC:
          cout << "SC" << endl; continue;
        case ERR:
          errorHandler(token); break;
        case DONE:
          cout << "DONE" << endl; break;
      }
    }
  }

  // most common identifier statistic
  static void mciMode(vector<Token> tokens) {
    map<string, int> idents;
    tuple<string, int> mci("", -1);
    auto lexeme = get<0>(mci);

    for(auto token : tokens) {
      if(token.GetTokenType() == IDENT) {
        if(tokens.back().GetTokenType() == ERR)
          return;

        auto lexeme = token.GetLexeme();

        if(!idents[lexeme])
          idents[lexeme] = 1;

        else
          idents[lexeme]++;
      }
    }

    for(auto ident : idents) {
      if(ident.second > 1) {
        get<0>(mci) = ident.first;
        get<1>(mci) = ident.second;
      }
    }

    cout << "Most Common Identifier: " << get<0>(mci) << endl;
  }

  // sum statistic mode
  static void sumMode(istream* in, vector<Token> tokens) {
    if(tokens.back().GetTokenType() == ERR)
      return;

    int totalLines, totalTokens, totalStrings, longestString;
    char c;

    in->clear();
    in->seekg(0, ios::beg);

    while(in->get(c)) {
      if(c == '\n')
        totalLines++;
    }

    for(auto token : tokens) {
      totalTokens++;

      if(token.GetTokenType() == SCONST) {
        int len = token.GetLexeme().length();
        totalStrings++;

        if(longestString == 0)
          longestString = len;

        if(len > longestString)
          longestString = len;
      }
    }

    cout << "Total lines: " << totalLines << endl;
    cout << "Total tokens: " << totalTokens << endl;
    cout << "Total strings: " << totalStrings << endl;
    cout << "Length of longest string: " << (longestString - 2) << endl; // subtract two for quotes
  }
};

#endif
