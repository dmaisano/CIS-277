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

  Value *Add(Value *right) {
    // if adding two strings
    if(this->GetType() == STRTYPE && right->GetType() == STRTYPE)
      return new Value(this->GetStrValue() + right->GetStrValue());

    // if adding two ints
    else if(this->GetType() == INTTYPE && right->GetType() == INTTYPE)
      return new Value(this->GetIntValue() + right->GetIntValue());

    // error
    else {
      throw runtime_error("addition type error! please make sure types are the same");
      return new Value();
    }
  }

  Value *Multiply(Value *right) {
    // int multiplication
    if(this->GetType() == INTTYPE && right->GetType() == INTTYPE)
      return new Value(this->GetIntValue() * right->GetIntValue());
    // error
    else if(this->GetType() == STRTYPE && right->GetType() == STRTYPE) {
      throw runtime_error("Cannot multiply " + this->GetStrValue() + " and " + right->GetStrValue());
      return new Value();
    }
    // string int multiplication
    int times = this->GetType() == INTTYPE ? this->GetIntValue() : right->GetIntValue();
    string str = "", res = "";

    // determine if the left or right node contains the string
    if(this->GetType() == STRTYPE)
      str = this->GetStrValue();
    else
      str = right->GetStrValue();
    
    for(int i = 0; i < times; i++)
      res += str;

    return new Value(res);
  }

  Value *Bracket(Value *left, Value *right) {
    int beginBracket, endBracket;
    string res;

    
  }
};

#endif

