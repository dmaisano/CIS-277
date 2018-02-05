#include <iostream>
#include <string>
#include <sstream> // splitString()
#include <fstream> // files
#include <vector> // vector<type>
#include <map> // map<type, type>
#include <algorithm> // find
#include <cctype> // check whitespace
#include "../lex.h"
using namespace std;

void argsFunc(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  // string spaces = "  this is  a    string with  spaces";
  // string res = Lex::squish(spaces);
  // cout << res << endl << "Length: " << res.length() << " chars" << endl;
}

// main prog (handles command line args)
void argsFunc(int argc, char *argv[]) {
  vector<string> files; // stores a list of file args
  vector<string> flags; // stores a list of flag args
  map<string, string> flagMap; // dictionary for flags

  flagMap["-q"] = "Quiet Mode";
  flagMap["-s"] = "Squish Mode";
  flagMap["-c"] = "Censor Mode";
  flagMap["-p"] = "Print Mode";
  flagMap["-l"] = "Length Mode";

  if(argc <= 1) {
    cout << "MISSING ARGS" << endl;
    return;
  }

  for(int i = 0; i < argc; i++) {
    // finds flags
    if(argv[i][0] == '-') {
      // of the valid is valid, add it to the list of flags
      if(flagMap.count(argv[i]))
        flags.push_back(argv[i]);

      else {
        cout << argv[i] << " INVALID FLAG" << endl;
        exit(0);
      }
    }

    // finds file flags
    else if(i != 0)
      files.push_back(argv[i]);
  }
  
  // Conflicting flags
  for(auto const flag : flags)
    if((Lex::inFlags(flags, "-s") || Lex::inFlags(flags, "-c")) && Lex::inFlags(flags, "-q")) {
      cout << "CONFLICTING FLAGS" << endl;
      return;
    }

  // Too many files
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
