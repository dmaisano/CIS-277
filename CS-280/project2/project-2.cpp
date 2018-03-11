#include <iostream>
#include <string>
#include <vector>
#include "./cli.h"
#include "./project-2.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  CLI::Main(argc, args);
}
