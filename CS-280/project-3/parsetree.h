/*
* parsetree.h
*/

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <vector>
#include <map>
#include "./lexer.h"
using std::vector;
using std::map;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

// Parse Tree ADT
class ParseTree {
	int			  linenum;
	ParseTree	*left;
	ParseTree	*right;

public:
  // initialized constructor
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
    : linenum(linenum), left(l), right(r) {}

  // destructor
	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }

	virtual NodeType GetType() const { return ERRTYPE; }

  // can be overwritten by inherited classes 
  virtual int isPlus()        { return 0; }
  virtual int isTimes()       { return 0; }
  virtual int isBracket()     { return 0; }
  virtual int isEmptyString() { return 0; }
};


// prototypes
ParseTree *Prog(istream *in, int *line);
ParseTree *Slist(istream *in, int *line);
ParseTree *Stmt(istream *in, int *line);
ParseTree *VarStmt(istream *in, int *line);
ParseTree *SetStmt(istream *in, int *line);
ParseTree *PrintStmt(istream *in, int *line);
ParseTree *RepeatStmt(istream *in, int *line);
ParseTree *Expr(istream *in, int *line);
ParseTree *Term(istream *in, int *line);
ParseTree *Factor(istream *in, int *line);
ParseTree *Primary(istream *in, int *line);


// statement list
class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
};


// variable declaration
class VarDecl : public ParseTree {};


// assignment
class Assignment : public ParseTree {};


// print statement
class Print : public ParseTree {
public:
	Print(int line, ParseTree *e) : ParseTree(line, e) {}
};


// repeat
class Repeat : public ParseTree {};


// plus
class PlusExpr : public ParseTree {
public:
  PlusExpr(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
  int isPlus() { return 1; }
};


// minus
class MinusExpr : public ParseTree {};


// multiplication
class TimesExpr : public ParseTree {
public:
  TimesExpr(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
  int isPlus() { return 1; }
};


// slice
class SliceExpr : public ParseTree {};


// slice operand
class SliceOperand : public ParseTree {};


// integer
class IConst : public ParseTree {
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }
};


// string
class SConst : public ParseTree { };


// identifier
class Ident : public ParseTree { };


#endif /* PARSETREE_H_ */
