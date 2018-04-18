/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* interpreter.h
*/

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
  // stores a map of variables with their respective values
  map<string,Value*> symbols;

  auto prog = Parser::Parse(in, trace);

  if(prog)
    cout << "valid program" << endl;

  prog->Interpret(symbols);
};

}

#endif
