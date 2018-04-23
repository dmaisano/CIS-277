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
  
  virtual Value *GetValue(map<string,Value*> &state) { return 0; }

  // called when slicing
  virtual void SliceEval(map<string,Value*> &state, Value* &begin, Value* &end) {}
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
  void Eval(map<string,Value*> &state) {
    auto expr = left->GetValue(state);

    if(expr->GetType() != INTTYPE)
      throw runtime_error(to_string(linenum) + ": REPEAT must contain integer expression to evaluate");

    int times = expr->GetIntValue();

    if(times < 0) {
      cout << "RUNTIME ERROR: Cannot contain negative integer expression in Repeat stmt" << endl;
      exit(0);
      // throw runtime_error("RUNTIME ERROR: Cannot contain negative integer expression in Repeat stmt");
    }

    for(int i = 0; i < times; i++)
      right->Eval(state);
  }
};


class PlusExpr : public ParseTree {
public:
	PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  Value *GetValue(map<string,Value*> &state) {
    return Value::Add(left->GetValue(state), right->GetValue(state));
  }
};

class MinusExpr : public ParseTree {
public:
	MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  Value *GetValue(map<string,Value*> &state) {
    return Value::Subtract(left->GetValue(state), right->GetValue(state));
  }
};

class TimesExpr : public ParseTree {
public:
	TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  Value *GetValue(map<string,Value*> &state) {
    return Value::Multiply(left->GetValue(state), right->GetValue(state));
  }
};

class SliceExpr : public ParseTree {
public:
	SliceExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  void SliceEval(map<string,Value*> &state, Value* &begin, Value* &end) {
    if(right)
      right->SliceEval(state, begin, end);
  }

  Value* GetValue(map<string,Value*> &state) {
    Value* s = left->GetValue(state);
    Value* begin = new Value();
    Value* end = new Value();

    if(s->GetType() != STRTYPE)
      throw runtime_error(to_string(linenum) + ": Can only slice string");

    // syntactic sugar
    SliceEval(state, begin, end);

    string str = s->GetStrValue(), res;
    int b = begin->GetIntValue();
    int e =  (end->GetIntValue() - b) + 1;
    int size = str.length();

    if(b < 0 || b < 0) {
      cout << "RUNTIME ERROR: Slice length cannot be negative" << endl;
      exit(0);
    }

    if(b > size || e > size) {
      cout << ("RUNTIME ERROR: Slice length cannot exceed string length") << endl;
      exit(0);
    }

    res = str.substr(b,e);

    return new Value(res);
  }
};

class SliceOperand : public ParseTree {
public:
	SliceOperand(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

  void SliceEval(map<string,Value*> &state, Value* &begin, Value* &end) {
    string errmsg = to_string(linenum) + ": Slice value(s) cannot be negative";

    if(left) {
      if(left->GetValue(state)->GetType() != INTTYPE)
        throw runtime_error(errmsg);

      begin = left->GetValue(state);
    }

    if(right) {
      if(right->GetValue(state)->GetType() != INTTYPE)
        throw runtime_error(errmsg);

      end = right->GetValue(state);
    }

    if(!left && !right ) {
      throw runtime_error(to_string(linenum) + ": Slice Error");
    }
  }
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
