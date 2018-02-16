#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <map>
#include <set>
using namespace std;

class Lex {
public:
  // function to handle the CLI program
  static void argsFunc(int argc, vector<string> argv) {
    set<string> options = { "-q", "-s", "-c", "-p", "-l" };

    // stores a set of flag args that will be used when parsing
    set<string> parserFlags = {};

    bool foundFile = false;
    string fileName = "";

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
          fileName = arg;
          foundFile = true;
        }

        // more than one file
        else if(foundFile == true) {
          cout << "TOO MANY FILES" << endl;
          exit(0);
        }
      }
    }

    // this is such an elegant solution for finding flags :)
    if(inFlags(parserFlags, {"-s", "-c", "-p"})) {
      cout << "CONFLICTING FLAGS" << endl;
      exit(0);
    }

    // will eventually open a file
    else {
      cout << fileName << " CANNOT OPEN" << endl;
      exit(0);
      // auto parsedFile = parse(fileName, );
    }
  }

  // returns true if flag is found
  static bool inFlags(set<string> flags, vector<string> args) {
    for(auto arg : args) {
      if(flags.find(arg) != flags.end())
        continue; else return false;
    } return true;
  }

  // returns a list of words per each line
  static vector<vector<string>> findWords(const string fileName, string squish = "-s", const char delim = ' ') {
    // continues if file exists, if not exits program
    if(ifstream(fileName))
      ; else exit(0);

    vector<vector<string>> result;
    ifstream file(fileName);
    string curLine = "";

    while(getline(file, curLine)) {
      vector<string> words = {};
      istringstream ss(curLine);
      string word = "";

      // does not append empty lines to our list
      if(curLine.empty() && squish == "-s") {
        continue;
      }

      // iterates over each word per line
      while(ss >> word) {
        string tmp = ""; // current word in line
        bool foundChar = false;

        // iterates over each character per word
        for(auto c : word) {
          // executes if any non-whitespace char is found
          if(!isspace(c)) {
            tmp += c;
            foundChar = true;
          }

          // executes if any whitespace is found after the word/char
          else if((isspace(c) && foundChar) || (foundChar && c == delim))
            break;
        }

        words.push_back(tmp);
      }

      result.push_back(words);
    }

    return result;
  }


  // will parse a file with the provided list of flags
  static vector<vector<string>> parseFile(const string fileName, const vector<string> flags) {
    // do something
  }
};

#endif 
