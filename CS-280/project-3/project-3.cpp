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

int main(int argc, char *argv[])
{
	// argv vector
	vector<string> args(argv + 1, argv + argc);

	CLI::Main(argc, args);
}
