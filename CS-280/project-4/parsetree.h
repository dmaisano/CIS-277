/*
* parsetree.h
*/

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "./lexer.h"
#include "./value.h"
using namespace std;

// NodeType represents all possible types
// enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

class ParseTree {
protected:
	int			  linenum;
	ParseTree	*left;
	ParseTree	*right;

public:
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
    : linenum(linenum), left(l), right(r) {}

	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }

	int Traverse(int input, int (ParseTree::*func)(void)) {
		if(left)  input += left->Traverse(input, func);
		if(right) input += right->Traverse(input, func);
		return Visit(input, func);
	}

	virtual NodeType GetType() const { return ERRTYPE; }

	virtual int Visit(int input, int (ParseTree::*func)(void)) {
		return input;
	}

	virtual bool   IsIdent() const { return false; }
	virtual bool   IsVar()   const { return false; }
	virtual string GetId()   const { return "";    }

	void GetVars(map<string,bool>& var) {
		if(left)
      left->GetVars(var);
		if(right)
      right->GetVars(var);
		if(IsVar())
			var[this->GetId()] = true;
	}

	virtual void Eval(map<string,Value*> &state) {
    if(left)
      left->Eval(state);
    if(right)
      right->Eval(state);
  }

  // overloaded functions
  virtual Value *GetValue(map<string,Value*> &state) { return 0; }
  // virtual Value *GetValue() { return 0; }
};

class StmtList : public ParseTree {
public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}

	// int Visit(int input, int (ParseTree::*func)(void)) {
	// 	for( auto s : statements ) {
	// 		input += s->Visit(input, func);
	// 	}
	// 	return input;
	// }
};

class VarDecl : public ParseTree {
private:
	string id;

public:
	VarDecl(Token& t, ParseTree *ex) : ParseTree(t.GetLinenum(), ex), id(t.GetLexeme()) {}

	bool   IsVar() const { return true; }
	string GetId() const { return id; }

  void Eval(map<string,Value*> &state) {
    // error, var is already declared
    if(state[id]) {
      throw runtime_error(to_string(linenum) + ": Cannot redefine var " + id + " use SET stmt");
      exit(0);
    }

    state[id] = left->GetValue(state);
  }
};

class Assignment : public ParseTree {
	string id;

public:
	Assignment(Token& t, ParseTree *e) : ParseTree(t.GetLinenum(), e), id(t.GetLexeme()) {}

  void Eval(map<string,Value*> &state) {
    auto type = state[id]->GetType();
    auto exprType = left->GetValue(state)->GetType();

    // type checking
    if(type != exprType)
      throw runtime_error(to_string(linenum) + ": Type error");

    state[id] = left->GetValue(state);
  }
};

class Print : public ParseTree {
public:
	Print(int line, ParseTree *e) : ParseTree(line, e) {}

  void Eval(map<string,Value*> &state) {
    auto val = left->GetValue(state);

    if(val->GetType() == INTTYPE)
      cout << val->GetIntValue() << endl;

    else if(val->GetType() == STRTYPE)
      cout << val->GetStrValue() << endl;
  }
};

class Repeat : public ParseTree {

public:
	Repeat(int line, ParseTree *e, ParseTree *s) : ParseTree(line, e, s) {}

  // num to repeat must be non-negative
};


class PlusExpr : public ParseTree {
public:
	PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  Value *Add(Value *left, Value *right) {

    if(left->GetType() == INTTYPE && right->GetType() == INTTYPE)
      return new Value(left->GetIntValue() + right->GetIntValue());

    else if(left->GetType() == STRTYPE && right->GetType() == STRTYPE)
      return new Value(left->GetStrValue() + right->GetStrValue());

    // error
    throw runtime_error("RUNTIME ERROR: Addition type error! please make sure types are the same");
    return new Value();
  }

  Value *GetValue(map<string,Value*> &state) {
    return Add(left->GetValue(state), right->GetValue(state));
  }
};

class MinusExpr : public ParseTree {
public:
	MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  Value *Subtract(Value *left, Value *right) {
    if(left->GetType() == INTTYPE && right->GetType() == INTTYPE)
      return new Value(left->GetIntValue() - right->GetIntValue());

    else if(left->GetType() == STRTYPE && right->GetType() == STRTYPE) {
      string str = left->GetStrValue(), substr = right->GetStrValue();
      auto pos = str.find(substr);

      // replace the first occurence of the found substring
      if(pos != string::npos)
        str.replace(pos, substr.length(), "");

      return new Value(str);
    }

    // error
    throw runtime_error("RUNTIME ERROR: Subtraction type error! please make sure types are the same");
    return new Value();
  }

  Value *GetValue(map<string,Value*> &state) {
    return Subtract(left->GetValue(state), right->GetValue(state));
  }
};

class TimesExpr : public ParseTree {
public:
	TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  Value *Multiply(Value *left, Value *right) {
    if(left->GetType() == INTTYPE && right->GetType() == INTTYPE)
      return new Value(left->GetIntValue() * right->GetIntValue());

    // error
    else if(left->GetType() == STRTYPE && right->GetType() == STRTYPE) {
      throw runtime_error("RUNTIME ERROR: Cannot multiply " + left->GetStrValue() + " and " + right->GetStrValue());
      return new Value();
    }

    // string int multiplication
    int times = left->GetType() == INTTYPE ? left->GetIntValue() : right->GetIntValue();
    string str = "", res = "";

    // determine if the left or right node contains the string
    if(left->GetType() == STRTYPE)
      str = left->GetStrValue();
    else
      str = right->GetStrValue();
    
    for(int i = 0; i < times; i++)
      res += str;

    return new Value(res);
  }

  Value *GetValue(map<string,Value*> &state) {
    return Multiply(left->GetValue(state), right->GetValue(state));
  }
};

class SliceExpr : public ParseTree {
public:
	SliceExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class SliceOperand : public ParseTree {
public:
	SliceOperand(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class IConst : public ParseTree {
private:
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }

  Value *GetValue(map<string,Value*> &state) {
    return new Value(val);
  }
};

class SConst : public ParseTree {
private:
	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	NodeType GetType() const { return STRTYPE; }

  Value *GetValue(map<string,Value*> &state) {
    return new Value(val);
  }
};

class Ident : public ParseTree {
private:
	string id;

public:
	Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}

	bool IsIdent() const { return true; }
	string GetId() const { return id; }

  Value *GetValue(map<string,Value*> &state) {
    // get the value;
    auto val = state[id];
    return val;
  }
};

#endif
