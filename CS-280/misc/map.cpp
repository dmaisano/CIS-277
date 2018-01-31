#include <iostream>
#include <map>
using namespace std;

int main() {
  map<string, string> flags;

  flags["-q"] = "Quiet Mode";
  flags["-s"] = "Squish Mode";
  flags["-c"] = "Censor Mode";
  flags["-p"] = "Print Mode";
  flags["-l"] = "Length Mode";

  // iterate over keys and values of map
  for(auto &flag : flags) {
    cout << flag.first << "\t" << flag.second << endl;
  }
  
  return 0;
}
