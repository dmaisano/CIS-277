#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include "./projlex.h"
using namespace std;

class Lex {
public:
  // exposes the main functionality of the program
  static string CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> parserFlags, flags = { "-v", "-mci", "-sum" };
    bool foundFile;
    string fileName;

    // exit quietly if no args
    if(argc == 1) {
      exit(0);
    }

    for(auto arg : argv) {
      // any argument beginning with '-' are flags
      if(arg[0] == '-') {
        // executes if valid value is found
        if(inFlags(flags, arg))
          parserFlags.insert(arg);

        else {
          cout << "INVALID FLAG " << arg << endl;
          exit(0);
        }
      }

      // finds files
      else {
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

    // finds conflicting flags

    // FINALLY. we lex the file!

    // exit program when done
    exit(0);
  }

private:
  // returns true if the flag provided is found
  static bool inFlags(const set<string> flags, string arg) {
    for(auto flag : flags)
      if(flag == arg)
        return true;
    return false;
  }
};

#endif
