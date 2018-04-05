/*
 * parsetree.h
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <vector>
#include <map>
using std::vector;
using std::map;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

class ParseTree {
	int			linenum;
	ParseTree	*left;
	ParseTree	*right;

public:
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)//this line
		: linenum(linenum), left(l), right(r) {}//and this line are used

	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }

	virtual NodeType GetType() const { return ERRTYPE; }
};

class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}//ParseTree(0, l, r)over here to assign values automatically
};

class VarDecl : public ParseTree {
	
public:
	VarDecl(int *my_line_pointer, ParseTree *my_left_pointer) :
	ParseTree(*my_line_pointer, my_left_pointer){}//my_line_pointer has to have the * because it needs to get dereferenced and get the actual value from the main3.cpp which is an int and my_left_pointer doesn't have the * because it goes as a pointer. Please take a look at class ParseTree, it needs a type int, type ParseTree pointer and type ParseTree pointer Also can I do? ParseTree(*my_line_pointer, my_left_pointer,0)
	
};


class Assignment : public ParseTree {
	
public:
	Assignment(int *my_line_pointer, ParseTree *my_left_pointer) :
	ParseTree(*my_line_pointer, my_left_pointer){}//this is the same as VarDecl
};

class Print : public ParseTree {
public:
	Print(int line, ParseTree *e) : ParseTree(line, e) {}
};

class Repeat : public ParseTree {
	
public:
	Repeat()
};

class PlusExpr : public ParseTree {};

class MinusExpr : public ParseTree {};

class TimesExpr : public ParseTree {};

class SliceExpr : public ParseTree {};

class SliceOperand : public ParseTree {};

class IConst : public ParseTree {
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }
};

class SConst : public ParseTree { };

class Ident : public ParseTree { };


#endif /* PARSETREE_H_ */
