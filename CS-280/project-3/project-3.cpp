/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* project-3.cpp
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "./cli.h"
using namespace std;

vector<Token> getAllTokens() {
  vector<Token> tokens;
  Token tok;

  return tokens;
}

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);

  CLI::CLI(argc, args);
}
