#include <iostream>
#include <string>
#include <vector>
#include "./project-2.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  Lex::CLI(argc, args);
}
