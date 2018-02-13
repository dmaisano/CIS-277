#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <map>
#include <vector>
using namespace std;

void openFile(string fileName);
bool is_good_word(string);
bool is_real_word(string);
bool is_cap_word(string);
bool is_acryonym(string);
// this returns a dictionary that contains all word types
map<string, vector<string>> flagHandler(ifstream file, map<string, int> flags);

class Token {
public:
  Token(string tokenName) {
    map<string, vector<string>> token;
  }
}

class Lex {
public:
  // function to handle the CLI
  static void argsFunc(int argc, vector<string> argv) {
    map<string, string> flagMap = {
      { "-q", "Quiet Mode"  },
      { "-s", "Squish Mode" },
      { "-c", "Censor Mode" },
      { "-p", "Print Mode"  },
      { "-l", "Length Mode" },
    };

    // stores a dict of flag args
    map<string, int> flags = {
      // the int value stores the count of the flag
      { "-q", 0 },
      { "-s", 0 },
      { "-c", 0 },
      { "-p", 0 },
      { "-l", 0 },
    };

    bool foundFile = false;
    string file = "";

    if(argc == 1) {
      cout << "MISSING ARGS" << endl;
      return;
    }

    for(auto arg : argv) {
      // finds flags
      if(arg[0] == '-') {
        if(flagMap.count(arg))
          ++flags[arg];

        else {
          cout << arg << " INVALID FLAG" << endl;
          return;
        }
      }

      // finds files
      else {
        if(foundFile == false) {
          file = arg;
          foundFile = true;
        }

        else if(foundFile == true) {
          cout << "TOO MANY FILES" << endl;
          return;
        }
      }
    }

    for(auto const flag : flags)
      if((inFlags(flags, "-s") || inFlags(flags, "-c")) && inFlags(flags, "-q")) {
        cout << "CONFLICTING FLAGS" << endl;
        return;
      }

    // will eventually open a file
    else {
      cout << file << " CANNOT OPEN" << endl;
      return;
    }
  }

  static vector<string> splitString(const string str) {
    stringstream ss(str);
    string item;

    // returns list of words
    vector<string> res;

    while(ss >> item) {
      string temp = "";
      bool foundChar = false;

      // loops over each character in strin 'item'
      for(auto c : item) {
        // executes if any non-whitespace char is found
        if(!isspace(c)) {
          temp += c;
          foundChar = true;
        }

        // executes if any whitespace is found after the word/char
        if(isspace(c) && foundChar)
          break;
      }

      // appends word to the list
      res.push_back(temp);
    }

    return res;
  }

  static string squish(string s) {
    if(s == "") {
      cout << "NO STRING PROVIDED" << endl;
      return "";
    }
    
    string res = "";
    auto items = splitString(s);

    for(auto item :  items)
      res += item + " ";

    res.pop_back(); // removes the trailing space at the end of the string
    return res;
  }

  // returns true if flag is found
  static bool inFlags(map<string, int> flags, string f) {
    if(flags[f] > 0)
      return true;

    return false;
  }
};

void openFile(string fileName) {
    // executes if file exists
    if(fstream(fileName))
      ; // does nothing

    else {
      cout << fileName << " CANNOT OPEN" << endl;
      return;
    }

    ifstream file(fileName);
    string line = "";

  while(getline(file, line))
    cout << line << endl;
}

bool is_good_word(string word) {
  for(auto c : word)
    cout << c;
}

// Will handle file with included flag options (ie. Squish, Quiet, etc)
map<string, vector<string>> flagHandler(ifstream file, map<string, int> flags) {
  map<string, vector<string>> tokens;
}

#endif 
