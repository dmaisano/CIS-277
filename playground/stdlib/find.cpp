#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool inFlags(vector<string>, string);

int main()
{
	vector<string> v = {"-q", "-s", "-c", "-p", "-l"};

	cout << inFlags(v, "-s");
}

bool inFlags(vector<string> flags, string flag)
{
	if (find(flags.begin(), flags.end(), flag) != flags.end())
		return true;

	return false;
}
