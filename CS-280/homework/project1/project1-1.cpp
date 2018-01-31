#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
// #include <cctype>
// #include <algorithm>
using namespace std;

void argsFunc(int argc, char *argv[], map<string, string> flags) {
  vector<string> args;

  for(int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  if(argc <= 1) {
    cout << "MISSING ARGS";
    return;
  }

  for(auto const &arg : args) {
    cout << arg << endl;
  }
}

int main(int argc, char *argv[]) {
  // vector<string> flags = { "q", "-s", "-c", "-p", "-l" };
  map<string, string> flags;

  flags["-q"] = "Quiet Mode";
  flags["-s"] = "Squish Mode";
  flags["-c"] = "Censor Mode";
  flags["-p"] = "Print Mode";
  flags["-l"] = "Length Mode";

  argsFunc(argc, argv, flags);

  // iterate over keys and values of map
  // for(auto const &flag : flags) {
  //   cout << flag.first << "\t" << flag.second << endl;
  // }
}
