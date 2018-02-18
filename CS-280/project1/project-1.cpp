#include <iostream>
#include <string>
#include <vector>
#include "./parser.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  // Parser::main(argc, args);

  set<string> options = { "-c" };
  auto parsedFile = Parser::parse("./sample.txt", options);

  cout << parsedFile;

  cout << "\n[done]";


  // auto copyFile = Parser::copyFile("./sample.txt");

  // int empty = 0;
  // for(auto line : copyFile)
  //   for(auto c : line)
  //     if(c == '\n')
  //       ++empty;

  // cout << empty;
}
