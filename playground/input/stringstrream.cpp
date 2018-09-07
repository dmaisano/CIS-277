#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;

int main()
{
	vector<string> words;
	string foo = "  this file has      sev3ral      Extra      words!   ";
	string tmp;
	bool foundWord = false;
	bool foundWS = false;
	int size = foo.size() - 1;

	for (int i = 0; i <= size; i++)
	{
		if (words.empty() && isspace(foo[i]))
		{
			tmp += foo[i];
		}

		if (!isspace(foo[i]) && !foundWS)
		{
			tmp += foo[i];
			foundWord = true;
		}

		else if (isspace(foo[i]) && foundWord)
		{
			tmp += foo[i];
			foundWord = false;
			foundWS = true;
		}

		else if (isspace(foo[i]) && !foundWord && foundWS)
		{
			tmp += foo[i];
		}

		else if (!isspace(foo[i]) && !foundWord && foundWS)
		{
			words.push_back(tmp);
			tmp = foo[i];
			foundWord = true;
			foundWS = false;
		}

		if (i == size)
			words.push_back(tmp);
	}

	for (auto word : words)
	{
		for (auto c : word)
		{
			if (c == ' ')
				cout << "*";
			else
				cout << c;
		}
		cout << "\\n\n";
	}
}
