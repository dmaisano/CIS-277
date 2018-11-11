#include "lexer.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  int lineNumber = 0;

  Token tok;

  istream *in = &cin;
  ifstream file;

  bool vflag = false;
  bool allidsflag = false;
  bool sumflag = false;

  int tokCount = 0;
  int stringCount = 0;
  int identCount = 0;
  map<TokenType, int> counts;
  map<string, bool> identifiers;

  for (int i = 1; i < argc; i++) {
    string arg(argv[i]);
    if (arg == "-v")
      vflag = true;
    else if (arg == "-allids")
      allidsflag = true;
    else if (arg == "-sum")
      sumflag = true;
    else if (arg[0] == '-') {
      cerr << "INVALID FLAG " << arg << endl;
      return 0;
    } else if (in != &cin) {
      cerr << "TOO MANY FILE NAMES" << endl;
      return 0;
    } else {
      file.open(arg);
      if (file.is_open() == false) {
        cerr << "UNABLE TO OPEN " << arg << endl;
        return 0;
      }

      in = &file;
    }
  }

  while ((tok = getNextToken(in, &lineNumber)) != DONE && tok != ERR) {
    if (vflag)
      cout << tok << endl;

    ++tokCount;
    if (tok == SCONST) {
      stringCount++;
    } else if (tok == IDENT) {
      identCount++;
      identifiers[tok.GetLexeme()] = true;
    }
  }

  if (tok == ERR) {
    cout << "Error on line " << lineNumber << " (" << tok.GetLexeme() << ")" << endl;
    return 0;
  }

  if (allidsflag && identifiers.size() > 0) {
    cout << "IDENTIFIERS: ";
    auto it = identifiers.begin();
    cout << it->first;

    for (it++; it != identifiers.end(); it++)
      cout << ", " << it->first;
    cout << endl;
  }

  if (sumflag) {
    cout << "Total lines: " << lineNumber << endl;
    cout << "Total tokens: " << tokCount << endl;
    if (tokCount > 0) {
      cout << "Total identifiers: " << identCount << endl;
      cout << "Total strings: " << stringCount << endl;
    }
  }

  return 0;
}
