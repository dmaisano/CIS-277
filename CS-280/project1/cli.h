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
#include <map>
#include <regex>
using namespace std;

class PatternMatcher {
public:
  // encapsulate's main functionality of the program
  static string CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> parserFlags = {}, options = { "-q", "-s", "-c", "-p", "-l" };
    bool foundFile = false;
    string fileName;

    // if no args provided
    if(argc == 1) {
      cout << "MISSING ARGS" << endl;
      exit(0);
    }

    for(auto arg : argv) {
      // any argument beginning with '-' are flags
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

          // if file cannot be found
          if(ifstream(fileName).fail()) {
            cout << fileName << " CANNOT OPEN" << endl;
            exit(0); 
          }

          foundFile = true;
        }

        // if a file is already found
        else if(foundFile == true) {
          cout << "TOO MANY FILES" << endl; exit(0);
        }
      }
    }

    // finds conflicting flags
    if((inFlags(parserFlags, {"-s"}) || inFlags(parserFlags, {"-c"})) && inFlags(parserFlags, {"-q"})) {
      cout << "CONFLICTING FLAGS" << endl;
      exit(0);
    }

    // FINALLY. we parse the file!

    // contains the count of each type of word
    map<string, int> wordCount = {
      { "goodword", 0 },
      { "realword", 0 },
      { "capword",  0 },
      { "acronym",  0 }
    };



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

  // returns an exact copy of each line in the file
  static vector<string> copyFile(const string fileName) {
    vector<string> copiedFile;
    ifstream file(fileName);
    string curLine;
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

  // increments the occurence of the wordtype
  static void wordType(string str, map<string, int>& wordCount) {
    bool goodWord = true, realWord = true, capWord = false, acronym = true;

    istringstream ss(str);
    string trimmedWord;
    // removes whitespace from the current word
    ss >> trimmedWord;

    if(isupper(trimmedWord[0]))
      capWord = true;

    // checks if word is a goodword
    for(auto c : trimmedWord) {
      if(isalnum(c))
        continue;
      else {
        goodWord = false;
        break;
      }
    }

    // checks if word is a realword
    for(auto c : trimmedWord) {
      if(isalnum(c))
        continue;
      else {
        realWord = false;
        break;
      }
    }

    // checks if word is an acronym
    for(auto c : trimmedWord) {
      if(isupper(c))
        continue;
      else {
        acronym = false;
        break;
      }
    }

    if(goodWord)
      wordCount["goodword"];

    if(realWord)
      wordCount["realword"];

    if(capWord)
      wordCount["capword"];

    if(acronym)
      wordCount["acronym"];
  }

  // returns a vector of strings within a search string that match the given pattern
  vector<string> findWords(const string str) {
    const regex pattern(R"([\s]*[\w|.!?]+[\s]*)");
    sregex_iterator it(str.begin(), str.end(), pattern), reg_end;
    vector<string> words;

    // reg_end == empty/null iterator
    for(; it != reg_end; ++it)
      words.push_back(it->str());

    return words;
  }

  // returns a string containing all the lines of the parsed file
  static string parse(const string fileName, const set<string> args = {}) {
    string parsedFile;

    return parsedFile;
  }
};

#endif 
