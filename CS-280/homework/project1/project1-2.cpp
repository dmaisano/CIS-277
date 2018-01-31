#include <iostream>
#include <string>
#include <sstream> // splitString()
#include <fstream> // files
#include <vector> // vector<type>
#include <map> // map<type, type>
#include <algorithm> // find
#include <cctype> // check whitespace
using namespace std;

void argsFunc(int argc, char *argv[]); // program1
bool inFlags(vector<string> flags, string flag); // returns true if flag is found
vector<string> splitString(const string &str, const char delim) {
  stringstream ss(str);
  string item;

  vector<string> res;

  while(getline(ss, item, delim))
    res.push_back(item);

  return res;
}

int main(int argc, char *argv[]) {
  // vector<string> flags = { "q", "-s", "-c", "-p", "-l" };
  map<string, string> flags;

  flags["-q"] = "Quiet Mode";
  flags["-s"] = "Squish Mode";
  flags["-c"] = "Censor Mode";
  flags["-p"] = "Print Mode";
  flags["-l"] = "Length Mode";

  vector<string> split = splitString("Hello World", ' ');

  for(auto const &x : split) {
    cout << x << endl;
  }

  // iterate over keys and values of map
  // for(auto const &flag : flags) {
  //   cout << flag.first << "\t" << flag.second << endl;
  // }
}


vector<string> splitString(const string &str, const char delim) {
  stringstream ss(str);
  string item;

  vector<string> res;

  while(getline(ss, item, delim))
    res.push_back(item);

  return res;
}


void argsFunc(int argc, char *argv[]) {
  // vector<string> temp(argv, argv + argc); // copy of argv
  // vector<string> flagTypes = { "-q", "-s", "-c", "-p", "-l" };
  map<string, string> flagMap;
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

bool inFlags(vector<string> flags, string flag) {
  if(find(flags.begin(), flags.end(), flag) != flags.end())
    return true;
  
  return false;
}
