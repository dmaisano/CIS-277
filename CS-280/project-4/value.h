/*
* value.h
*/

#ifndef VALUE_H_
#define VALUE_H_

#include <iostream>
#include <string> 
using namespace std;

// manually defining NodeType here allows for
// 'value.h' to be included in 'parsetree.h'
// and avoid cyclic dependency issues
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

class Value {
	int	ival;
	string sval;
	NodeType type;

public:
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

#endif
