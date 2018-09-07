#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string fileName = "../../project1/sample.txt";
	ifstream file(fileName);
	string parsed;
	char c;
	int count = 0;

	while (file.get(c))
	{
		++count;
		parsed += c;
	}

	cout << count << " characters" << endl
			 << parsed;

	file.close();
}
