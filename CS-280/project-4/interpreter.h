#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "./parser.h"
#include "./value.h"
using namespace std;

namespace Interpreter {

static void Interpret(istream *in, bool trace) {
  Parser::Parse(in, trace);
};

}

#endif
