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
#include <string>
#include <fstream>
#include <set>
#include "./parser.h"
using namespace std;

extern bool inSet(set<string> args, string str) {
  for(auto arg : args)
    if(arg == str)
      return true;
    
  return false;
};

namespace CLI {
  // exposes the main functionality of the program
  static void CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> parserFlags, flags = { "-t" };
    bool foundFile;
    string fileName;

    // exit quietly if no args
    if(argc == 1) {
      exit(0);
    }

    for(auto arg : argv) {
      // flag handler
      if(arg[0] == '-') {
        // executes if valid flag is found
        if(inSet(flags, arg))
          parserFlags.insert(arg);

        else {
          cout << "UNKNOWN FLAG " << arg << endl;
          exit(0);
        }
      }

      // file handler
      else if(arg[0] != '-') {
        if(foundFile == false) {
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
          cout << "TOO MANY FILE NAMES" << endl; exit(0);
        }
      }
    }

    ifstream file(fileName);
    istream* in = &file;
    // finally we can actually run the program
    // Parser::Parse(in);
    cout << "I RAN!";

    cout << endl;
    exit(0); // exit the program
  }
};

#endif
