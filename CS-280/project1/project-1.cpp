#include <iostream>
#include <string>
#include <sstream>    // splitString()
#include <fstream>    // files
#include <vector>     // vector<type>
#include <map>        // map<type, type>
#include <algorithm>  // find()
#include <cctype>     // check whitespace
#include "./parser.h"
using namespace std;

int main(int argc, char *argv[]) {
  // vector of args
  vector<string> args(argv + 1, argv + argc);

  // "\n**NEWLINE**\n"

  // Parser::main(argc, args);

  // auto file = Parser::copyFile("./sample.txt");
  auto wordlist = Parser::findWords("./x.txt");
  vector<string> newLine = {"\\n\n"};

  for(auto line : wordlist) {
    string currentLine;
    currentLine = accumulate(begin(line), end(line), currentLine);

    // if(currentLine == "\n" || currentLine.empty())
    //   continue;

    // for(auto word : line) {
    //   if(word != line[line.size()-2])
    //     cout << word << " ";
    //   else
    //     cout << word;
    // }
  }
}
