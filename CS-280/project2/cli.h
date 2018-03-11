#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include "./lexer.h"
using namespace std;

class CLI {
public:
  // exposes the main functionality of the program
  static void Main(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> userFlags, validFlags = { "-q", "-s", "-c", "-p", "-l"  };
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
        if(inSet(validFlags, arg))
          userFlags.insert(arg);

        else {
          cout << "INVALID FLAG " << arg << endl;
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
            cout << "UNABLE TO OPEN " << fileName << endl;
            exit(0); 
          }
        }

        // if a file is already found
        else if(foundFile == true) {
          cout << "TOO MANY FILE NAMES" << endl; exit(0);
        }
      }
    }
    
    // finally we can actually run the program
    ifstream file(fileName);
    istream* in = &file;
    Lex::Lexer(in, userFlags);

    exit(0); // exit the program
  }
};

#endif
