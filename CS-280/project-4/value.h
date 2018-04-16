/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* value.h
*/

#ifndef VALUE_H_
#define VALUE_H_

#include "./parsetree.h"
using namespace std;

class Value {
private:
	int	ival;
	string sval;
	NodeType type;

public:
  // constructor options
	Value()         : ival(0),type(ERRTYPE) {}
	Value(int i)    : ival(i),type(INTTYPE) {}
	Value(string s) : ival(0),sval(s),type(STRTYPE) {}

	NodeType GetType() const { return type; }

	int GetIntValue() const {
		if(type != INTTYPE)
      throw runtime_error("using GetIntValue on a Value that is not an INT");
		return ival;
	}

	string GetStrValue() const {
		if(type != STRTYPE)
			throw runtime_error("using GetStrValue on a Value that is not a STRING");
		return sval;
  }
};


Value *Add(Value *left, Value *right) {
  if(left->GetType() == INTTYPE && right->GetType() == INTTYPE)
    return new Value(left->GetIntValue() + right->GetIntValue());

  else if(left->GetType() == STRTYPE && right->GetType() == STRTYPE)
    return new Value(left->GetStrValue() + right->GetStrValue());

  // error
  throw runtime_error("RUNTIME ERROR: Addition type error! please make sure types are the same");
  return new Value();
}


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

// ???
Value *SliceValues(Value *left, Value *right) {
  int beginBracket, endBracket;
  string res;
}


Value PrintValue(Value *expr) {
  // return nothing if there is no object
  if(!expr)
    return;

  if(expr->GetType == STRTYPE)
    cout << expr->GetStrValue() << endl;

  else
    cout << expr->GetIntValue() << endl;
}

#endif

