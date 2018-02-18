#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <ctype.h>
#include <vector>
#include <set>
using namespace std;

vector<string> findWords(string line);

class Parser {
public:
  // encapsulate's main functionality of the program
  static string CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> parserFlags = {}, options = { "-q", "-s", "-c", "-p", "-l" };
    bool foundFile = false;
    string fileName = "";

    if(argc == 1) { cout << "MISSING ARGS" << endl; exit(0); }

    for(auto arg : argv) {
      // args beginning with '-' are flags
      if(arg[0] == '-') {
        // executes if valid value is found
        if(checkFlags(options, {arg}))
          parserFlags.insert(arg);

        else { cout << arg << " INVALID FLAG" << endl; exit(0); }
      }

      // finds files
      else {
        if(foundFile == false) {
          fileName = arg;
          // continues if file exists, if not exits program
          if(ifstream(fileName)) ;
          else { cout << fileName << " CANNOT OPEN" << endl; exit(0); }
          foundFile = true;
        }

        else if(foundFile == true) { cout << "TOO MANY FILES" << endl; exit(0); }
      }
    }

    // finds conflicting flags
    if((checkFlags(parserFlags, {"-s"}) || checkFlags(parserFlags, {"-c"})) && checkFlags(parserFlags, {"-q"})) {
      cout << "CONFLICTING FLAGS" << endl;
      exit(0);
    }

    // parses the file
    else {
      auto parsedFile = parse(fileName, parserFlags);
      return parsedFile;
    }
  }

  // returns true if all flag(s) are found
  static bool checkFlags(const set<string> flags, vector<string> args) {
    for(auto arg : args) {
      if(flags.find(arg) != flags.end())
        continue;
      else return false;
    }
    return true;
  }

  // returns true if the flag provided is found
  static bool inFlags(const set<string> flags, string arg) {
    for(auto flag : flags)
      if(flag == arg)
        return true;
    return false;
  }

  // returns an exact copy / list of words per line in the file
  static vector<string> copyFile(const string fileName) {
    vector<string> copiedFile;
    ifstream file(fileName);
    string curLine = "";
    char c;

    // loop through the entire file, one char at a time
    while(file.get(c)) {
      curLine += c;
      if(c == '\n') {
        copiedFile.push_back({curLine});
        // reinitalizes the current line to an empty string
        curLine = "";
      }
    }

    file.close();
    return copiedFile;
  }

  bool validateWord(string str) {
    for(auto c : str)
      if(!isalpha(c))
        return false;
      return true;
  }

  // returns a list of words per each line
  static string parse(const string fileName, const set<string> args = {}) {
    string parsedFile;
    vector<string> currentLine;
    auto file = copyFile(fileName);

    // if(args == set<string>{})
    //   return file;

    for(auto line : file) {
      bool validWord = false, foundWord = false;
      string currentWord, whitespace;
      vector<string> words, whitespace;

      if(args == set<string>{}) {
        parsedFile += line;
        continue;
      }

      // iterates over each char in the line
      for(auto c : line) {
        if(!inFlags(args, "-s"))
          ;

        if(inFlags(args, "-c"))
          ;

        if(!isspace(c) && isalpha(c)) {
          currentWord += c;
          validWord = true;
        }

        if(isspace(c) && validWord) {
          currentWord += c;
          foundWord = false;
        }

        if(!isspace(c) && !isalpha(c)) {
          foundWord = true;
          validWord = false;
        }
        parsedFile += currentWord;
        currentWord = "";
      }
    }
    return parsedFile;
  }
};

vector<string> findWords(string line) {
  vector<string> res; // result to be returned
  istringstream ss(line);
  string item;

  // iterates over each word per line
  while(ss >> item) {
    cout << item; continue;
    string tmp = "";
    bool foundChar = false;

    // iterates over each character per word
    for(auto c : item) {
      // executes if any non-whitespace char is found
      if(!isspace(c)) {
        tmp += c;
        foundChar = true;
      }

      // executes if any whitespace is found after the word/char
      if(isspace(c) && foundChar)
        break;
    }

    res.push_back(tmp);
  }

  return res;
}

#endif 
