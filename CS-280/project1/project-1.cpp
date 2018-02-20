#include <iostream>
#include <string>
#include <vector>
#include "./cli.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  // PatternMatcher::CLI(argc, args);

  set<string> options = { "-q", "-s", "-c", "-p", "-l" };
  set<string> parserFlags = { "-c" };

  // auto parsedFile = PatternMatcher::parse("./sample.txt", options);
  // cout << parsedFile;

  auto squished = PatternMatcher::squishLine("  this file has      sev3ral      Extra      words!   ", parserFlags);

  auto parsedFile = PatternMatcher::parse("./sample.txt", parserFlags);

  // cout << parsedFile;

  for(auto c : parsedFile) {
    if(c ==  ' ')
      cout << '*';
    else if(c == '\n')
      cout << "\\n\n";
    else if(!isspace(c))
      cout << c;
  }

  // auto realWords = PatternMatcher::

  // for(auto c : squished) {
  //   if(c == ' ')
  //     cout << "*";
  //   else
  //     cout << c;
  // }

  cout << "\n[done]";
}
