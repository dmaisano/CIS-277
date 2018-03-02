#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include "./project-2.h"
using namespace std;

class CLI {
public:
  // exposes the main functionality of the program
  CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> cliFlags, flags = { "-v", "-mci", "-sum" };
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
        if(inFlags(flags, arg))
          cliFlags.insert(arg);

        else {
          cout << "INVALID FLAG " << arg << endl;
          exit(0);
        }
      }

      // file handler
      else if(arg[0] != '-') {
        if(foundFile == false) {
          fileName = arg;

          // if file cannot be found
          if(ifstream(fileName).fail()) {
            cout << "UNABLE TO OPEN " << fileName << endl;
            exit(0); 
          }

          foundFile = true;
        }

        // if a file is already found
        else if(foundFile == true) {
          cout << "TOO MANY FILE NAMES" << endl; exit(0);
        }
      }
    }

    // FINALLY. we lex the file!
    Lexer(fileName);

    exit(0); // exit the program
  }
};

#endif
