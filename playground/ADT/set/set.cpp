#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
	set<string> flags = {"-q", "-s", "-c", "-p", "-l"};

	bool q = flags.find("-q") != flags.end();

	cout << q;
}
