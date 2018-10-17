// #include "lexer.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  vector<string> args(argv + 1, argv + argc);
  // int lineNum = 0;

  istream *in = &cin;
  ifstream file;

  // bool verbose = false;
  // bool sum = false;
  // bool allIds = false;

  for (auto arg : args) {
    if (arg == "-v") {
      // verbose = true;
    }

    else if (arg == "-sum") {
      // sum = true;
    }

    else if (arg == "-allids") {
      // allIds = true;
    }

    else if (arg[0] == '-') {
      cerr << "INVALID FLAG " << arg << endl;
      return 0;
    }

    else if (in != &cin) {
      cerr << "TOO MANY FILE NAMES" << endl;
      return 0;
    }

    else {
      file.open(arg);

      if (file.is_open() == false) {
        cerr << "UNABLE TO OPEN " << arg << endl;
        return 0;
      }

      in = &file;
    }
  }

  // run the lexer
  // Token tok;
  // while ((tok = getNextToken(in, &lineNum)) != DONE && tok != ERR) {

  // }
}
