#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main () {
  map<string, string> flags;

  flags["-q"] = "Quiet Mode";
  flags["-s"] = "Squish Mode";
  flags["-c"] = "Censor Mode";
  flags["-p"] = "Print Mode";
  flags["-l"] = "Length Mode";

  // auto iter = flags.find("-q");
  // if(iter != flags.end())
  //   flags.erase(iter);

  // print content:
  // cout << "elements in mymap:" << "\n";
  // cout << "-s => " << flags.find("-s")->second << "\n";
  // cout << "-c => " << flags.find("-c")->second << "\n";
  // cout << "-p => " << flags.find("-p")->second << "\n";

  vector<string> flagTypes = { "-q", "-s", "-c", "-p", "-l" };

  // string word = "-q";

  for(auto const flag : flagTypes)
    if(flags.count(flag))
      cout << flags[flag] << endl;
}
