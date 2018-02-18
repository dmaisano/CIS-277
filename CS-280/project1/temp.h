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
  static void argsFunc(int argc, vector<string> argv) {
    set<string> options = { "-q", "-s", "-c", "-p", "-l" };

    // stores a set of flag args that will be used when parsing
    set<string> parserFlags;

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

          // continues if file exists, if not exits program
          if(ifstream(fileName))
            ;
          
          else {
            cout << fileName << " CANNOT OPEN" << endl;
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

    // this is such an elegant solution for finding flags :)
    if((inFlags(parserFlags, {"-s"}) || inFlags(parserFlags, {"-c"})) && inFlags(parserFlags, {"-q"})) {
      cout << "CONFLICTING FLAGS" << endl;
      exit(0);
    }

    // will eventually open a file
    else {
      exit(0);
    }
  }

  // returns true if flag is found
  static bool inFlags(set<string> flags, vector<string> args) {
    for(auto arg : args) {
      if(flags.find(arg) != flags.end())
        continue;
      else return false;
    }
    return true;
  }

  // returns a list of words per each line
  static vector<vector<string>> findWords(const string fileName, set<string> parserFlags, const char delim = ' ') {
    vector<vector<string>> result;
    ifstream file(fileName);
    string curLine = "";

    // iterate over each line in the file
    while(getline(file, curLine)) {
      vector<string> words = {};
      istringstream ss(curLine);
      string word = "";
      // does not append empty lines to our list
      if(curLine.empty() && inFlags(parserFlags, {"-s"}))
        continue;
      // iterates over each word per line
      while(ss >> word) {
        string tmp = ""; // current word in line
        bool foundWord = false;
        // iterates over each character per word
        for(auto c : word) {
          // executes if any non-whitespace char is found
          if(!isspace(c)) {
            tmp += c;
            foundWord = true;
          }
          // executes if whitespace or delim is found after the word
          else if((isspace(c) && foundWord) || (foundWord && c == delim))
            break;
        }
        tmp += " ";
        words.push_back(tmp);
      }
      string temp;
      for(auto c : words.back()) {
        if(!isspace(c))
          temp += c;
      }
      words.back() = temp += "\n";
      result.push_back(words);
    }
    file.close();
    return result;
  }

  static vector<string> copyFile(const string fileName) {
    vector<string> copiedFile;
    ifstream file(fileName);
    string curLine = "";
    char c;

    // loop through the entire file, one char at a tune
    while(file.get(c)) {
      curLine += c;
      if(c == '\n') {
        copiedFile.push_back(curLine);
        curLine = "";
      }
    }

    file.close();
    return copiedFile;
  }

  // returns a list of good words
  static vector<vector<string>> goodWords(const set<string> parserFlags) {
    vector<vector<string>> goodWordsList;

    return goodWordsList;
  }
};

#endif 
