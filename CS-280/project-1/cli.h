/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* cli.h
*/

#ifndef CLI_H_
#define CLI_H_

#include <iostream>
#include <cctype>
#include <fstream>
#include <vector>
#include <map>
#include "./pattern-matcher.h"
using namespace std;

namespace CLI {
  // exposes the main functionality of the program
  static void Main(int argc, vector<string> argv) {
    map<string,bool> parserFlags = {
      {"-q", 0},
      {"-s", 0},
      {"-c", 0},
      {"-p", 0},
      {"-l", 0}
    };

    istream *in = &cin;
    ifstream file;
    bool foundFile = false;

    for(auto arg : argv) {
      // flag handler
      if(arg[0] == '-')
        findFlags(parserFlags, arg);

      // error handler
      else if(foundFile) {
        cerr << "TOO MANY FILENAMES" << endl;
        exit(0);
      }

      // file handler
      else {
        file.open(arg);
        foundFile = true;

        if(file.is_open() == false) {
          cerr << "COULD NOT OPEN " << arg << endl;
          exit(0);
        }
      }

      in = &file;
    }
    // run the program
    PatternMatcher::match(in, parserFlags);
  }
};

#endif
