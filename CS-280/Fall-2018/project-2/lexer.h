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

// map that returns the string value for each ENUM type
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

// overload the operator to output information about our token
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
        // if the char isn't any of the options contained in the switch
        // statement then return an error by default
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
        case '=':
          tt = ASSIGN;
          break;
        case '==':
          tt = EQ;
          break;
        case '!=':
          tt = NEQ;
          break;
        case '>':
          tt = GT;
          break;
        case '>=':
          tt = GEQ;
          break;
        case '<':
          tt = LT;
          break;
        case '<=':
          tt = LEQ;
          break;
        case '&&':
          tt = LOGICAND;
          break;
        case '||':
          tt = LOGICOR;
          break;
        }

        // finally we return the token
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

#endif
