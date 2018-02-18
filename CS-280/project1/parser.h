#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <ctype.h>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

class Parser {
public:
  // encapsulate's main functionality of the program
  static void CLI(int argc, vector<string> argv) {
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

    // parses the file//
    else {
      // auto parsedFile = parseFile(fileName, parserFlags);
      
      // for(auto line : parsedFile)
      //   for(auto word : line)
      //     cout << word;

      exit(0);
    }
  }

  // returns true if the flag(s) are found
  static bool inFlags(const set<string> flags, vector<string> args) {
    for(auto arg : args) {
      if(flags.find(arg) != flags.end())
        continue;
      else return false;
    }
    return true;
  }

  // returns a list of words per each line
  static vector<vector<string>> findWords(const string fileName) {
    vector<vector<string>> wordlist;
    auto file = Parser::copyFile(fileName);

    for(auto line : file) {
      string currentLine;
      currentLine = accumulate(begin(line), end(line), currentLine);
      vector<string> words;
      istringstream ss(line);
      string item;

      if(currentLine.empty() || currentLine == "\n")
       cout << "\\n\n";
      else
        cout << currentLine;

      // iterates over each word per line
      while(ss >> item) {
        string word = "";
        bool foundChar = false;

        // iterates over each character per word
        for(auto c : item) {
          // executes if any non-whitespace char is found
          if(!isspace(c)) {
            word += c;
            foundChar = true;
          }
          // executes if any whitespace is found after the word/char
          if(isspace(c) && foundChar)
            break;
        }
        words.push_back(word);
      }
      words.push_back("\n");
      wordlist.push_back(words);
    }
    return wordlist;
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

  // will parse a file with the provided list of flags
  static vector<string> parseFile(const string fileName, const set<string> parserFlags) {
    auto wordlist = findWords(fileName);
    vector<string> parsedFile;

    // return exact copy of file
    // if(parserFlags.empty())
    //   return copyFile(fileName);

    // return no output
    // else if(inFlags(parserFlags, {"-q"}))
    //   return parsedFile;

    // else if(inFlags(parserFlags, {"-s"}))
    //   return findWords(fileName, {"-s"});

    // else if(inFlags(parserFlags, {"-c"}))
      // return realWords(wordlist, "realword");

    return parsedFile;
  }
};

#endif 
