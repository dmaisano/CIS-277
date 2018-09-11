/*
 * Domenico Maisano
 * CS280
 * Spring 2018
 *
 * cli.h
 */

#ifndef CLI_H_
#define CLI_H_

#include "./parser.h"
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

namespace CLI {
// exposes the main functionality of the program
static void Main(int argc, vector<string> argv) {
  istream *in = &cin;
  ifstream file;
  bool traceMode = false;

  for (auto arg : argv) {
    // flag handler
    if (arg[0] == '-') {
      // executes if valid flag is found
      if (arg == "-t")
        traceMode = true;

      else {
        cout << "UNKNOWN FLAG " << arg << endl;
        exit(0);
      }
    }
    // error handler
    else if (in != &cin) {
      cerr << "TOO MANY FILENAMES" << endl;
      exit(0);
    }
    // file handler
    else {
      file.open(arg);
      if (file.is_open() == false) {
        cerr << "COULD NOT OPEN " << arg << endl;
        exit(0);
      }
    }

    in = &file;
  }
  // finally we can actually run the program
  Parser::Parse(in, traceMode);
}
}; // namespace CLI

#endif
