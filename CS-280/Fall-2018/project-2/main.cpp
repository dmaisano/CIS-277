#include "lexer.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  vector<string> args(argv + 1, argv + argc);

  istream *in = &cin;
  ifstream file;

  bool verbose = false;
  bool mci = false;
  bool sum = false;
  bool allIds = false;

  for (auto arg : args) {
    if (arg == "-v") {
      verbose = true;
    }

    else if (arg == "-mci") {
      mci = true;
    }

    else if (arg == "-sum") {
      sum = true;
    }

    else if (arg == "-allids") {
      allIds = true;
    }

    else if (arg[0] == '-') {
      cerr << "INVALID FLAG " << arg << endl;
      return 0;
    }

    else if (in != &cin) {
      cerr << "TOO MANY FILE NAMES" << endl;
      return 0;
    }

    else {
      file.open(arg);

      if (file.is_open() == false) {
        cerr << "UNABLE TO OPEN " << arg << endl;
        return 0;
      }

      in = &file;
    }
  }

  Token tok;
  int lineNum = 0;
  int tokenCount = 0, stringCount = 0, identCount = 0;
  map<TokenType, int> counts;
  map<string, bool> allStrings;
  map<string, int> allIdents;

  // run the lexer
  while ((tok = getNextToken(in, &lineNum)) != DONE && tok != ERR) {
    // increment num tokens
    ++tokenCount;

    // handle verbose mode
    if (verbose) {
      cout << tok << endl;
    }

    if (tok == SCONST) {
      stringCount++;
      allStrings[tok.GetLexeme()] = true;
    }

    else if (tok == IDENT) {
      identCount++;
      allIdents[tok.GetLexeme()]++;
    }
  }

  if (tok == ERR) {
    cout << "Error on line " << lineNum << " (" << tok.GetLexeme() << ")" << endl;
    return 0;
  }

  if (mci && allIdents.size() > 0) {
    cout << "Most Common Identifier: ";

    // find the largest counter in the map
    int maxcnt = 0;
    for (auto it : allIdents)
      if (it.second > maxcnt)
        maxcnt = it.second;

    // print all the identifiers
    // where it.second == maxcnt
    bool printed = false;
    for (auto it : allIdents) {
      if (it.second != maxcnt)
        continue;

      if (printed)
        cout << ", ";

      printed = true;
      cout << it.first;
    }
    cout << endl;
  }

  if (sum) {
    cout << "Total lines: " << lineNum << endl;
    cout << "Total tokens: " << tokenCount << endl;

    if (tokenCount > 0) {
      cout << "Total identifiers: " << identCount << endl;
      cout << "Total strings: " << stringCount << endl;
    }
  }

  if (allIds) {
  }
}
