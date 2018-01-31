#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
// #include <cctype>
// #include <algorithm>
using namespace std;

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
