#include <iostream>
#include <string>
#include "./parser.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  // Parser::main(argc, args);

  auto wordlist = Parser::findWords("./sample.txt");


  vector<string> foo;

  for(auto line : wordlist) {
    string currentLine;

    if(line == vector<string>{"\\0"}) {
      cout << "\\0\n";
      continue;
    }

    for(auto word : line) {
      if(word != line.back())
        cout << word << " ";
      else
        cout << word << endl;
    }
  }
}
