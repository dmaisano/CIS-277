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
using namespace std;

class PatternMatcher {
public:
  // exposes the main functionality of the program
  static string CLI(int argc, vector<string> argv) {
    // stores a set of flag args that will be used when parsing
    set<string> parserFlags, options = { "-q", "-s", "-c", "-p", "-l" };
    bool foundFile;
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
    parse(fileName, parserFlags);

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

  // returns an exact copy of each line in the file
  static vector<string> getFile(const string fileName) {
    vector<string> copyFile;
    ifstream file(fileName);
    string curLine;
    char c;

    // loop through the entire file, one char at a time
    while(file.get(c)) {
      curLine += c;
      if(c == '\n') {
        copyFile.push_back({curLine});
        // reinitalizes the current line to an empty string
        curLine = "";
      }
    }

    file.close();
    return copyFile;
  }

  // increments the occurences of the given word types
  static void classifyWord(string str, map<string, int>& wordCount) {
    int goodWord, realWord, capWord, acronym;
    istringstream ss(str);
    string word;
    ss >> word;  // removes whitespace from the current word

    if(isupper(word[0])) // checks if word is a capword
      capWord = word.size();

    // some magic happens here
    for(auto c : word) {
      if(isalnum(c)) // checks if word is a goodword
        ++goodWord;

      if(isalpha(c)) // checks if word is a realword
        ++realWord;

      if(isupper(c)) // checks if word is an acronym
        ++acronym;
    }

    if(goodWord == word.size())
      ++wordCount["goodword"];

    if(realWord == word.size())
      ++wordCount["realword"];

    if(capWord == word.size())
      ++wordCount["capword"];

    if(acronym == word.size())
      ++wordCount["acronym"];
  }

  // returns a vector of strings from a search string that matches the given pattern
  static vector<string> findWords(const string str, const string option = "") {
    regex pattern;
    sregex_iterator it(str.begin(), str.end(), pattern), reg_end;
    vector<string> wordlist;

    if(option != "-s")
      pattern.assign(R"([\s]*[\w|.!?]+[\s]*)");

    else if(option == "-s")
      pattern.assign((R"([\w|.!?]+)"))

    // reg_end == empty/null iterator
    for(; it != reg_end; ++it)
      wordlist.push_back(it->str());

    return wordlist;
  }

  /*
  TODO

  use getline with squishFile for easier use
  */

  // returns the file with whitespace trimmed
  static string squishFile(const string file) {
    string squishedFile;
    auto words = findWords(file, "-s");

    for(auto word : words) {
      if(word != words.back())
        tmp += word + " ";

      else if(word == words.back())
        tmp += word + "\n";
    }
  }


  static vector<string> printStats(vector<string> wordlist, map<string, int>& wordCount) {
    // do something
  }

  // parses the file, with the provided flags
  static string parse(const string fileName, const set<string> flags = {}) {
    string parsedFile;
    auto file = getFile(fileName);

    // contains the count of each type of word
    map<string, int> wordCount = {
      { "goodword", 0 },
      { "realword", 0 },
      { "capword",  0 },
      { "acronym",  0 }
    };

    // if no args, return the exact copy of file
    if(flags.empty())
      for(auto line : file)
        parsedFile += line;


    return parsedFile;
  }

  // static void output(const string parsedFile, const map<string, int> wordCount, const set<string> args = {}) {
    // handles the output of the program with the flags (quiet, stats, length)
  // }
};

#endif 
