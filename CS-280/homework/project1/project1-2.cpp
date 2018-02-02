#include <iostream>
#include <string>
#include <sstream> // splitString()
#include <fstream> // files
#include <vector> // vector<type>
#include <map> // map<type, type>
#include <algorithm> // find
#include <cctype> // check whitespace
#include "../lex.h";
using namespace std;

void argsFunc(int argc, char *argv[]);
bool inFlags(vector<string> flags, string flag);

int main(int argc, char *argv[]) {
  map<string, string> flags;
  flags["-q"] = "Quiet Mode";
  flags["-s"] = "Squish Mode";
  flags["-c"] = "Censor Mode";
  flags["-p"] = "Print Mode";
  flags["-l"] = "Length Mode";

  string spaces = "  this is  a    string with  spaces";
  string res = Lex::squish(spaces);
  cout << res << endl << "Length: " << res.length() << endl;
}

// handles command line args
void argsFunc(int argc, char *argv[]) {
  map<string, string> flagMap; // dictionary for flags
  vector<string> files; // stores a list of file args
  vector<string> flags; // stores a list of flag args

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
      if(flagMap.count(argv[i]))
        flags.push_back(argv[i]);

      else {
        cout << argv[i] << " INVALID FLAG" << endl;
        return;
      }
    }

    // finds file flags
    else if(i != 0)
      files.push_back(argv[i]);
  }

  // Conflicting flags
  for(auto const flag : flags)
    if((inFlags(flags, "-s") || inFlags(flags, "-c")) && inFlags(flags, "-q")) {
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

// returns true if flag is found
bool inFlags(vector<string> flags, string flag) {
  if(find(flags.begin(), flags.end(), flag) != flags.end())
    return true;
  
  return false;
}
