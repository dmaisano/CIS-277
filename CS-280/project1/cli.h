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

class PatternMatcher {
public:
  // encapsulate's main functionality of the program
  static string CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> parserFlags = {}, options = { "-q", "-s", "-c", "-p", "-l" };
    bool foundFile = false;
    string fileName;

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

  // returns the word if it is a realword
  static string isRealWord(string str) {
    istringstream ss(str);
    string item;

    // removes whitespace from the current word
    ss >> item;

    // iterate over each char in the word
    for(auto c : item) {
      if(isalpha(c))
        continue;
      else
        return "";
    }

    // if the word is valid, return it
    return item;
  }
  
  // removes extra whitespace from current line
  static string squishLine(const string str, const set<string> args) {
    istringstream ss(str);
    string result, item;

    if(!inFlags(args, "-c")) {
      while(ss >> item)
        result += item + " ";
    }

    else if(inFlags(args, "-c")) {
      // do something
    }
    

    // removes the additional space inserted by the loop
    result.pop_back();
    return result + "\n";
  }

  // true is a string is only whitespace
  static bool isWhiteSpace(const string str) {
    for(auto c: str) {
      if(!isspace(c))
        return false;
    }
    return true;
  }

  // finds all words in the line
  static vector<string> findWords(const string str) {
    vector<string> words;
    istringstream ss(str);
    string tmp;
    bool foundWord = false;
    bool foundWS = false;
    int size = str.size() - 1;

    for(int i = 0; i <= size; i++) {
      // appends anywhite to the word if found at the start of the line
      if(words.empty() && isWhiteSpace(tmp) && isspace(str[i]) && !foundWS) {
        tmp += str[i];
      }
      // if a character is found
      if(!isspace(str[i]) && !foundWS) {
        tmp += str[i];
        foundWord = true;
      }
      // appends the whitespace after a word
      else if(isspace(str[i]) && foundWord) {
        tmp += str[i];
        foundWord = false;
        foundWS = true;
      }
      // appends additional whitespace after the word 
      else if(isspace(str[i]) && !foundWord && foundWS) {
        tmp += str[i];
      }
      // if a word is found after the trailing whitespace of the previous word
      else if(!isspace(str[i]) && !foundWord && foundWS) {
        words.push_back(tmp);
        tmp = str[i];
        foundWord = true;
        foundWS = false;
      }
      // if the last word is found
      if(i == size)
        words.push_back(tmp);
    }

    return words;
  }

  // returns a list of words per each line
  static string parse(const string fileName, const set<string> args = {}) {
    string parsedFile;
    auto file = copyFile(fileName);
    vector<vector<string>> wordList;

    // if no args, return exact copy of file
    if(args == set<string>{} || checkFlags) {;
      for(auto line : file) {
        parsedFile += line;
        continue;
      }
      return parsedFile;
    }

    if(checkFlags(args, {"-s"})) {
      for(auto line : file) {
        parsedFile += squishLine(line);
      }
    }

    return parsedFile;
  }
};

#endif 
