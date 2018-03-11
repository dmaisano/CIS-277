#include <iostream>
#include <string>
#include <vector>
#include "./cli.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  // so neat, such wow, much amaze
  CLI::Main(argc, args);
}
