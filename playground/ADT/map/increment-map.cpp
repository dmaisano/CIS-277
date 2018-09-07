#include <iostream>
#include <string>
#include <map>
using namespace std;

void foo(string str, map<string, int> &bar)
{
	++bar[str];
}

int main()
{
	string str = "123";

	map<string, int> sample = {
			{"123", 0},
			{"abc", 0}};

	foo(str, sample);
	foo(str, sample);

	for (auto it : sample)
		cout << "key: " << it.first << "\tvalue: " << it.second << endl;
}
