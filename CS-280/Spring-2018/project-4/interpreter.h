/*
 * Domenico Maisano
 * CS280
 * Spring 2018
 *
 * interpreter.h
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "./parser.h"
#include "./value.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

namespace Interpreter {

static void Interpret(istream *in, bool trace) {
  // stores a map of variables with their respective values
  map<string, Value *> symbols;

  auto prog = Parser::Parse(in, trace);

  // evaluate the program
  prog->Eval(symbols);
};

} // namespace Interpreter

#endif
