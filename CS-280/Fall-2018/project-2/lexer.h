#ifndef LEXER_H_
#define LEXER_H_

#include "tokens.h"
#include <cctype>
#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
 * lexer.h
 */

// function prototype
TokenType complexLexeme(istream *in, char firstChar);

// map to convert enum to string
static map<TokenType, string> tokenPrint = {
    // keywords
    {PRINT, "PRINT"},
    {IF, "PRINT"},
    {THEN, "PRINT"},
    {TRUE, "TRUE"},
    {FALSE, "FALSE"},
    // identifier
    {IDENT, "IDENT"},
    // int & string
    {ICONST, "ICONST"},
    {SCONST, "SCONST"},
    // operators & more
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {STAR, "STAR"},
    {SLASH, "SLASH"},
    {ASSIGN, "ASSIGN"},
    {EQ, "EQ"},
    {NEQ, "NEQ"},
    {LT, "LT"},
    {LEQ, "LEQ"},
    {GT, "GT"},
    {GEQ, "GEQ"},
    {LOGICAND, "LOGICAND"},
    {LOGICOR, "LOGICOR"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {SC, "SC"},
    // terminators
    {ERR, "ERR"},
    {DONE, "DONE"}};

// overload the operator
ostream &operator<<(ostream &out, const Token &tok) {
  TokenType tt = tok.GetTokenType();

  out << tokenPrint[tt];

  if (tt == IDENT || tt == ICONST || tt == SCONST || tt == ERR)
    out << "(" << tok.GetLexeme() << ")";

  return out;
};

// map that returns the enum type for each keyword
static map<string, TokenType> keywordMap = {
    // clang-format off
    {"print", PRINT},
		{"if", IF},
		{"then", THEN},
		{"true", TRUE},
		{"false", FALSE},
    // clang-format on
};

// returns a token that is either an IDENT or possible keyword
Token ident_or_keyword(const string &lexeme, int linenum) {
  // ident by default
  TokenType tt = IDENT;

  // try to find a key using our keymap
  auto key = keywordMap.find(lexeme);

  // if a key is found, set it as the token type
  if (key != keywordMap.end())
    tt = key->second;

  return Token(tt, lexeme, linenum);
};

// return a token from the stream
Token getNextToken(istream *in, int *linenum) {
  enum LexState { BEGIN, INID, INSTRING, SAWMINUS, ININT, INCOMMENT } lexstate = BEGIN;
  // default state is BEGIN
  string lexeme;
  char ch;

  while (in->get(ch)) {
    // increment the linenum
    if (ch == '\n')
      (*linenum)++;

    switch (lexstate) {
    case BEGIN:
      // ignore whitespace
      if (isspace(ch))
        continue;

      // add the initial char to our lexeme
      lexeme = ch;

      if (isalpha(ch))
        lexstate = INID;
      else if (ch == '"')
        lexstate = INSTRING;
      else if (ch == '-')
        lexstate = SAWMINUS;
      else if (isdigit(ch))
        lexstate = ININT;
      else if (ch == '#')
        lexstate = INCOMMENT;

      else {
        // returns err by default
        TokenType tt = ERR;

        switch (ch) {
        case '+':
          tt = PLUS;
          break;
        case '-':
          tt = MINUS;
          break;
        case '*':
          tt = STAR;
          break;
        case '/':
          tt = SLASH;
          break;
        case '(':
          tt = LPAREN;
          break;
        case ')':
          tt = RPAREN;
          break;
        case ';':
          tt = SC;
          break;
        default:
          tt = complexLexeme(in, ch);
          break;
          // case '!=':
          //   tt = NEQ;
          //   break;
          // case '>':
          //   tt = GT;
          //   break;
          // case '>=':
          //   tt = GEQ;
          //   break;
          // case '<':
          //   tt = LT;
          //   break;
          // case '<=':
          //   tt = LEQ;
          //   break;
          // case '&&':
          //   tt = LOGICAND;
          //   break;
          // case '||':
          //   tt = LOGICOR;
          //   break;
        }

        // return the token once found
        return Token(tt, lexeme, *linenum);
      }
      break;

    case INID:
      if (isalpha(ch) || isdigit(ch))
        lexeme += ch;

      else {
        if (ch == '\n')
          (*linenum)--;

        in->putback(ch);
        return ident_or_keyword(lexeme, *linenum);
      }
      break;

    case INSTRING:
      lexeme += ch;

      if (ch == '\n')
        return Token(ERR, lexeme, *linenum);

      if (ch == '"') {
        // remove the quotation marks from the string
        lexeme = lexeme.substr(1, lexeme.length() - 2);
        return Token(SCONST, lexeme, *linenum);
      }
      break;

    case SAWMINUS:
      if (!isdigit(ch)) {
        if (ch == '\n')
          (*linenum)--;
        // putback the char to the stream
        in->putback(ch);
        return Token(MINUS, lexeme, *linenum);
      } else {
        lexeme += ch;
        lexstate = ININT;
      }
      break;

    case ININT:
      if (isdigit(ch)) {
        lexeme += ch;
      } else if (isalpha(ch)) {
        lexeme += ch;
        return Token(ERR, lexeme, *linenum);
      } else {
        if (ch == '\n')
          (*linenum)--;
        in->putback(ch);
        return Token(ICONST, lexeme, *linenum);
      }
      break;

    case INCOMMENT:
      if (ch != '\n')
        continue;

      if (ch == '\n')
        lexstate = BEGIN;

      break;
    }
  }

  // finished parsing file
  if (in->eof()) {
    return Token(DONE, "", *linenum);
  }

  // extraneous error
  return Token(ERR, "EXCEPTION CAUGHT", *linenum);
}

// returns the TokenType for lexemes with more than one char
TokenType complexLexeme(istream *in, char firstChar) {
  char nextChar;
  in->get(nextChar);

  // ASSIGN OR EQ
  if (firstChar == '=') {
    if (nextChar == '=') {
      return EQ;
    }

    else {
      // put back the character
      in->putback(nextChar);
      return ASSIGN;
    }
  }

  // NEQ
  else if (firstChar == '!') {
    if (nextChar == '=') {
      return NEQ;
    }

    else {
      // put back the character
      in->putback(nextChar);
    }
  }

  // LT or LEQ
  else if (firstChar == '<') {
    if (nextChar == '=') {
      return LEQ;
    }

    else {
      // put back the character
      in->putback(nextChar);
      return LT;
    }
  }

  // GT or GEQ
  else if (firstChar == '>') {
    if (nextChar == '=') {
      return GEQ;
    }

    else {
      // put back the character
      in->putback(nextChar);
      return GT;
    }
  }

  // LOGICAND
  else if (firstChar == '&') {
    if (nextChar == '&') {
      return LOGICAND;
    }

    else {
      // put back the character
      in->putback(nextChar);
    }
  }

  // LOGICOR
  else if (firstChar == '|') {
    if (nextChar == '|') {
      return LOGICOR;
    }

    else {
      // put back the character
      in->putback(nextChar);
    }
  }

  // else return ERR
  return ERR;
}

#endif
