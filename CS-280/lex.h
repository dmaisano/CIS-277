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

void flagHandler(ifstream fiel, map<string, int> flags);

class Lex {
public:
  // function to handle the CLI
  static void argsFunc(int argc, char *argv[]) {
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

    vector<string> files; // stores a list of file args

    if(argc <= 1) {
      cout << "MISSING ARGS" << endl;
      return;
    }

    for(int i = 0; i < argc; i++) {
      string arg = argv[i];

      // finds flags
      if(arg[0] == '-') {
        if(flagMap.count(arg))
          ++flags[arg];

        else {
          cout << argv[i] << " INVALID FLAG" << endl;
          return;
        }
      }

      // finds files
      else if(i != 0)
        files.push_back(argv[i]);
    }

    for(auto const flag : flags)
      if((inFlags(flags, "-s") || inFlags(flags, "-c")) && inFlags(flags, "-q")) {
        cout << "CONFLICTING FLAGS" << endl;
        return;
      }

    if(files.size() > 1) {
      cout << files.size() << " TOO MANY FILES" << endl;
      return;
    }

    // will eventually open a file
    else {
      cout << files[0] << " CANNOT OPEN" << endl;
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

      // loops over each character in 'item'
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

  void file(string fileName) {
  // executes if file exists
  if(fstream(fileName))
    ; // does nothing

  else {
    cout << fileName << " CANNOT OPEN" << endl;
    return;
  }

  ifstream file(fileName);
  string line = "";

  while(getline(file, line)) {
    cout << line << endl;
  }
}

};

// Will handle flag options (ie. Squish, Quiet, etc)
void flagHandler(ifstream fiel, map<string, int> flags) {
  // do something
}

#endif 
