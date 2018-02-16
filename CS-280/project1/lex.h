#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <set>
using namespace std;

class Lex {
public:
  // function to handle the CLI program
  void argsFunc(int argc, vector<string> argv) {
    set<string> options = { "-q", "-s", "-c", "-p", "-l" };\
    string fileName = "";

    // stores a set of flag args that will be used when parsing
    set<string> parserFlags;

    bool foundFile = false;

    if(argc == 1) {
      cout << "MISSING ARGS" << endl;
      exit(0);
    }

    for(auto arg : argv) {
      // args beginning with '-' are flags
      if(arg[0] == '-') {
        // executes if valid value is found
        if(inFlags(options, {arg}))
          parserFlags.insert(arg);

        else {
          cout << arg << " INVALID FLAG" << endl;
          exit(0);
        }
      }

      // finds files
      else {
        if(foundFile == false) {
          thisFile = arg;
          cout << "FOUND FILE: " << thisFile << endl << endl;

          // continues if file exists, if not exits program
          if(ifstream(thisFile))
            ;
          
          else {
            cout << thisFile << " CANNOT OPEN" << endl;
            exit(0);
          }

          foundFile = true;
        }

        else if(foundFile == true) {
          cout << "TOO MANY FILES" << endl;
          exit(0);
        }
      }
    }

    // finds if the flags passed conflict
    if((inFlags(parserFlags, {"-s"}) || inFlags(parserFlags, {"-c"})) && inFlags(parserFlags, {"-q"})) {
      cout << "CONFLICTING FLAGS" << endl;
      exit(0);
    }

    // open the file and parse it with the flags
    else {
      auto parsedFile = parseFile(thisFile, parserFlags);
      
      for(auto line : parsedFile)
        for(auto word : line)
          cout << word;

      exit(0);
    }
  }

  // returns true if flag(s) are found
  static bool inFlags(set<string> flags, vector<string> args) {
    for(auto arg : args) {
      if(flags.find(arg) != flags.end())
        continue;
      else return false;
    }
    return true;
  }

  // finds the list of words per each line
  static vector<string> findWords(const string fileName, parserFlags = {}, const char delim = ' ') {
    
  }

  // returns an exact copy of the file
  static vector<string> copyFile(const string fileName) {
    vector<vector<string>> copiedFile;
    ifstream file(fileName);
    string curLine = "";
    char c;

    // loop through the entire file, one char at a tune
    while(file.get(c)) {
      curLine += c;
      if(c == '\n') {
        copiedFile.push_back({curLine});
        curLine = "";
      }
    }

    file.close();
    return copiedFile;
  }

  // will parse a file with the provided list of flags
  static vector<vector<string>> parseFile(const string fileName, const set<string> parserFlags) {
    auto wordlist = findWords(fileName);
    vector<vector<string>> parsedFile;

    // return exact copy of file
    if(parserFlags.empty())
      return copyFile(fileName);

    // return no output
    else if(inFlags(parserFlags, {"-q"}))
      return parsedFile;

    else if(inFlags(parserFlags, {"-s"}))
      return findWords(fileName, {"-s"});

    else if(inFlags(parserFlags, {"-c"}))
      // return realWords(wordlist, "realword");

    return parsedFile;
  }
};

#endif 
