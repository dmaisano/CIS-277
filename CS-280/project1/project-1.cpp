#include <iostream>
#include <string>
#include <vector>
#include "./cli.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  // PatternMatcher::CLI(argc, args);

  set<string> options = { "-c" };

  // auto parsedFile = PatternMatcher::parse("./sample.txt", options);
  // cout << parsedFile;

  auto x = PatternMatcher::squishLine("  this file has      sev3ral      Extra      words!   ");
  auto y = PatternMatcher::squishLine("  this file has      sev3ral      Extra      words!   ");

  // cout << x << y;

  for(auto c : x) {
    if(c == ' ')
      cout << "*";
    else
      cout << c;
  }
  
  // for(auto word : words) {
  //   for(auto c : word) {
  //     if(c == ' ')
  //       cout << "*";
  //     else
  //       cout << c;
  //   }
  //   cout << "\\n\n";
  // }

  cout << "\n[done]";
}
