/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* parsetree.h
*/

#ifndef PARSETREE_H_
#define PARSETREE_H_
#include <iostream>
#include <vector>
#include <map>
#include "./lexer.h"
using namespace std;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

class ParseTree {
	int			linenum;
	ParseTree	*left;
	ParseTree	*right;

public:
  // constructor
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
		: linenum(linenum), left(l), right(r) {}

  // destructor
	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }

  ParseTree GetLeftChild() const { return *left; }

  ParseTree GetRightChild() const { return *right; }

	virtual NodeType GetType() const { return ERRTYPE; }
};


class StmtList : public ParseTree {
public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
};


class VarDecl : public ParseTree {
public:
  VarDecl(int line, ParseTree *ident, ParseTree *exp) : ParseTree(line, ident, exp) {}
};


class Assignment : public ParseTree {
public:
  Assignment(int line, ParseTree *ident, ParseTree *exp) : ParseTree(line, ident, exp) {}
};


class Print : public ParseTree {
public:
	Print(int line, ParseTree *exp) : ParseTree(line, exp) {}
};


class Repeat : public ParseTree {
public:
  Repeat(int line, ParseTree *times, ParseTree *exp) : ParseTree(line, times, exp) {}
};


class PlusExpr : public ParseTree {
public:
  PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
};


class MinusExpr : public ParseTree {
public:
  MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
};


class TimesExpr : public ParseTree {
public:
  TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
};


class SliceExpr : public ParseTree {
public:
  SliceExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
};


class SliceOperand : public ParseTree {
public:
  SliceOperand(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
};


class IConst : public ParseTree {
private:
	int val;
public:
	IConst(Token& tok) : ParseTree(tok.GetLinenum()) {
		val = stoi(tok.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }

  int getVal() const { return val; }
};


class SConst : public ParseTree {
private:
  string str;
public:
  SConst(Token& tok) : ParseTree(tok.GetLinenum()) {
    str = tok.GetLexeme();
  }
  
  NodeType GetType() const { return STRTYPE; }

  string getVal() const { return str; }
};


class Ident : public ParseTree {
private:
  string ident;
public:
  Ident(Token& tok) : ParseTree(tok.GetLinenum()) {
    ident = tok.GetLexeme();
  }

  string getVal() const { return ident; } 
};

#endif
