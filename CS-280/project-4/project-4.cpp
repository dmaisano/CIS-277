/*
 * Domenico Maisano
 * CS280
 * Spring 2018
 *
 * project-4.cpp
 */

#include "./cli.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  CLI::Main(argc, args);
}
