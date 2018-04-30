#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include "./cli.h"
using namespace std;

const int IN = 0;
const int OUT = 1;
const int NSTATS = 2;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  CLI::Main(argc, args);
}
