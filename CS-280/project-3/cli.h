/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* cli.h
*/

#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <fstream>
#include "./parser.h"
using namespace std;

namespace CLI {
  // exposes the main functionality of the program
  static void Parser(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    bool foundFile = false, traceMode = false;
    string fileName;

    // exit quietly if no args
    if(argc == 1)
      exit(0);

    for(auto arg : argv) {
      // flag handler
      if(arg[0] == '-') {
        // executes if valid flag is found
        if(arg == "-t")
          traceMode = true;

        else {
          cout << "UNKNOWN FLAG " << arg << endl;
          exit(0);
        }
      }

      // file handler
      else if(arg[0] != '-') {
        if(!foundFile) {
          fileName = arg;
          foundFile = true;

          // if file cannot be found
          if(ifstream(fileName).fail()) {
            cout << "COULD NOT OPEN " << fileName << endl;
            exit(0); 
          }
        }

        // if a file is already found
        else if(foundFile == true) {
          cout << "TOO MANY FILE NAMES" << endl;
          exit(0);
        }
      }
    }

    ifstream file(fileName);
    istream* in = &file;
    // finally we can actually run the program
    // Parser::Parse(in, traceMode);
    cout << "I RAN!";

    cout << endl;
    exit(0);
  }
};

#endif
