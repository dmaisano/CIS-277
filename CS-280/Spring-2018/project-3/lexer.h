#ifndef LEXER_H_
#define LEXER_H_

#include <cctype>
#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
 * projlex.h
 */

enum TType {
  // keywords
  SET,
  PRINT,
  VAR,
  REPEAT,
  // an identifier
  IDENT,
  // an integer and string constant
  ICONST,
  SCONST,
  // the operators, parens and semicolon
  PLUS,
  MINUS,
  STAR,
  COLON,
  LSQ,
  RSQ,
  LPAREN,
  RPAREN,
  SC,
  // any error returns this token
  ERR,
  // when completed (EOF), return this token
  DONE
};

class Token {
private:
  TType tt;
  string lexeme;
  int lnum;

public:
  Token() {
    tt = ERR;
    lnum = -1;
  }
  Token(TType tt, string lexeme, int line) {
    this->tt = tt;
    this->lexeme = lexeme;
    this->lnum = line;
  }

  bool operator==(const TType tt) const { return this->tt == tt; }
  bool operator!=(const TType tt) const { return this->tt != tt; }

  TType GetTokenType() const { return tt; }
  string GetLexeme() const { return lexeme; }
  int GetLinenum() const { return lnum; }
};

extern ostream &operator<<(ostream &out, const Token &tok);

extern Token getNextToken(istream *in, int *linenum);

/*
 * lexer.h
 */

// map that returns the string value for each ENUM type
static map<TType, string> tokenPrint = {
    // Reserved Words
    {SET, "SET"},
    {PRINT, "PRINT"},
    {VAR, "VAR"},
    {REPEAT, "REPEAT"},
    // Identifier
    {IDENT, "IDENT"},
    // Int & String
    {ICONST, "ICONST"},
    {SCONST, "SCONST"},
    // Operands
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {STAR, "STAR"},
    {COLON, "COLON"},
    {LSQ, "LSQ"},
    {RSQ, "RSQ"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {SC, "SC"},
    // Error & Done
    {ERR, "ERR"},
    {DONE, "DONE"}};

// overload the operator to output information about our token
ostream &operator<<(ostream &out, const Token &tok) {
  TType tt = tok.GetTokenType();

  out << tokenPrint[tt];

  if (tt == IDENT || tt == ICONST || tt == SCONST || tt == ERR)
    out << "(" << tok.GetLexeme() << ")";

  return out;
};

// map that returns the enum type for each keyword
static map<string, TType> keywordMap = {
    {"var", VAR},
    {"set", SET},
    {"print", PRINT},
    {"repeat", REPEAT},
};

// returns a token that is either an IDENT or possible keyword
Token ident_or_keyword(const string &lexeme, int linenum) {
  // ident by default
  TType tt = IDENT;

  // try to find a key using our keymap
  auto key = keywordMap.find(lexeme);

  // if a key is found, set it as the token type
  if (key != keywordMap.end())
    tt = key->second;

  return Token(tt, lexeme, linenum);
};

// return a token from the stream
Token getNextToken(istream *in, int *linenum) {
  enum LexState {
    BEGIN,
    INID,
    INSTRING,
    SAWMINUS,
    ININT,
    INCOMMENT
  } lexstate = BEGIN;
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
        TType tt = ERR;

        switch (ch) {
        case '+':
          tt = PLUS;
          break;
        case '*':
          tt = STAR;
          break;
        case ':':
          tt = COLON;
          break;
        case '[':
          tt = LSQ;
          break;
        case ']':
          tt = RSQ;
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

  if (in->eof())
    return Token(DONE, "", *linenum);
  return Token(ERR, "some strange I/O error", *linenum);
}

#endif
