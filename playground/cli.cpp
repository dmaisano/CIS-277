#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
	istream *in = &cin;
	ifstream file;

	vector<string> args(argv + 1, argv + argc);

	if (in->rdbuf()->in_avail() == 0)
	{
		cout << "something went wrong";
	}
	cout << endl;
	exit(0);
}
