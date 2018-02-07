#include <iostream>
#include <string>
#include <vector> // vector<type>
#include <map> // map<type, type>
#include <algorithm> // find]
using namespace std;

void argsFunc(int argc, char *argv[]); // basically program0
bool inFlags(map<string, int> flagMap, string flag); // returns true if flag is found

// main program
int main(int argc, char *argv[]) {
  argsFunc(argc, argv);
}

// function to handle the CLI
void argsFunc(int argc, char *argv[]) {
  // vector<string> temp(argv, argv + argc); // copy of argv
  // vector<string> flagTypes = { "-q", "-s", "-c", "-p", "-l" };
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

bool inFlags(map<string, int> flags, string f) {
  if(flags[f] > 0)
    return true;

  return false;
}
