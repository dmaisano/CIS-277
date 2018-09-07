#include <iostream>
using namespace std;

int hashFunc(char);
void countFrequency(string S);

int main()
{
	string letters = "ababcd";

	// O(n) time complexity
	// n being the # of chars in the string
	countFrequency(letters);

	return 0;
}

int hashFunc(char c)
{
	return c - 'a';
}

void countFrequency(string s)
{
	int freq[26]; // holds the frequency letters in the string

	for (int i = 0; i < 26; i++)
	{ // initializes the frequencies to zero
		freq[i] = 0;
	}

	for (int i = 0; i < s.length(); i++)
	{
		int index = hashFunc(s[i]);
		freq[index]++;
	}

	for (int i = 0; i < 26; i++)
	{
		cout << "Letter: " << (char)(i + 'a') << ",  Frequency: " << freq[i] << "\n";
	}
}
