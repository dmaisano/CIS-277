#include <iostream>
#include <string>
#include <sstream>    // splitString()
#include <fstream>    // files
#include <vector>     // vector<type>
#include <map>        // map<type, type>
#include <algorithm>  // find()
#include <cctype>     // check whitespace
#include "../lex.h"
using namespace std;

int main(int argc, char *argv[]) {
  // vector of args
  vector<string> args(argv + 1, argv + argc);

  string spaces = "  this is  a    string with  spaces   ";
  string res = Lex::squish(spaces);
  cout << res << endl << "Length: " << res.length() << " chars" << endl;

  // Lex::argsFunc(argc, args);
}

