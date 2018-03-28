#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
using namespace std;

// enum Token Type
// 0-17 Token Types
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

// Token Blueprint Class/ADT
class Token {
private:
	TType	  tt;       // token type
	string  lexeme;   // unit of the language
	int			lnum;     // line number

public:
  // constructor if no parameters passed
	Token() {
		tt = ERR;
		lnum = -1;
	}

  // constructor if required parameters passed
	Token(TType tt, string lexeme, int line) {
		this->tt = tt;
		this->lexeme = lexeme;
		this->lnum = line;
	}

  // returns the enum (tokentype) of the "token"
	TType GetTokenType() const {
    return tt;
  }

  // returns the "lexeme"
	string GetLexeme() const {
    return lexeme;
  }

  // returns the linenumber the token was found on
	int	GetLinenum() const {
    return lnum;
  }
};

#endif
