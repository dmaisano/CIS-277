#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
// #include <cctype>
// #include <algorithm>
using namespace std;

// stores an iteration of the flag map
map<string, string >::iterator iter;

void argsFunc(int argc, char *argv[]) {
  vector<string> temp(argv, argv + argc); // copy of argv
  // vector<string> flagTypes = { "-q", "-s", "-c", "-p", "-l" };
  map<string, string> flagMap;
  vector<string> nonFlags;
  vector<string> flags;

  flagMap["-q"] = "Quiet Mode";
  flagMap["-s"] = "Squish Mode";
  flagMap["-c"] = "Censor Mode";
  flagMap["-p"] = "Print Mode";
  flagMap["-l"] = "Length Mode";

  if(argc <= 1) {
    cout << "MISSING ARGS" << endl;
    return;
  }

  for(auto const &arg : temp) {
    // finds flags
    if(arg[0] == '-') {
      if(flagMap.count(arg))
        cout << "Flag: " << arg << "\tDesc: " << flagMap[arg] << endl;

      else
        cout << "Flag: " << arg << "\tINVALID FLAG" << endl;
    }
  }
}

int main(int argc, char *argv[]) {
  argsFunc(argc, argv);
}
