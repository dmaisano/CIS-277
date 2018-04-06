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
enum NodeType { ERRTYPE, INTTYPE, STRTYPE, PLUSTYPE, MINUSTYPE, TIMESTYPE, BRACKTYPE, NULLSTRTYPE };

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
  
};


class PlusExpr : public ParseTree {
public:
  PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
  NodeType GetType() const { return PLUSTYPE; }
};


class MinusExpr : public ParseTree {
public:
  MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
  NodeType GetType() const { return MINUSTYPE; }
};


class TimesExpr : public ParseTree {
public:
  TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}
  NodeType GetType() const { return TIMESTYPE; }
};


class SliceExpr : public ParseTree {

};


class SliceOperand : public ParseTree {

};


class IConst : public ParseTree {
private:
	int val;
public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
	NodeType GetType() const { return INTTYPE; }
};


class SConst : public ParseTree {
private:
  string str;
public:
  SConst(Token& t) : ParseTree(t.GetLinenum()) {
    str = t.GetLexeme();
  }
  NodeType GetType() const { return STRTYPE; }
};


class Ident : public ParseTree {
private:
  Token identTok;
public:
  Ident(const Token& identTok) : ParseTree(0), identTok(identTok) {}
};

#endif /* PARSETREE_H_ */
