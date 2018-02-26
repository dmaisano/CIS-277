/*
 * projlex.h
 *
 * CS280
 * Spring 2018
 * 
 * contains my personal comments
 */

#ifndef PROJLEX_H_
#define PROJLEX_H_

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

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

class Token {
	TType	  tt;     // token type
	string  lexeme; // unit of the language, one or more words
	int			lnum;   // line number

public:
  // constructor if no parameters passed
	Token() {
		tt = ERR;
		lnum = -1;
	}

  // constructor if parameters passed
	Token(TType tt, string lexeme, int line) {
		this->tt = tt;
		this->lexeme = lexeme;
		this->lnum = line;
	}

  // defining comparison operators
	bool operator == (const TType tt) const { return this->tt == tt; }
	bool operator != (const TType tt) const { return this->tt != tt; }

  // returns the enum of the "token"
	TType GetTokenType() const {
    return tt;
  }
  // returns the "lexeme"
	string GetLexeme() const {
    return lexeme;
  }
  // returns the total number of lines
	int	GetLinenum() const {
    return lnum;
  }
};

// function && operator defined, but not yet written
extern ostream& operator << (ostream& out, const Token& tok);
extern Token getNextToken(istream *in, int *linenum);


#endif /* PROJLEX_H_ */
