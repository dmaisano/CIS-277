/*
* CS280 - Spring 2018
* Lexical Analyzer test engine
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "./projlex.h"
#include "./lexer.h"
using namespace std;

int main(int argc, char *argv[]) {
  // argv vector
  vector<string> args(argv + 1, argv + argc);
	int lineNumber = 0;

	Token	tok;
	istream *in = &cin;
	ifstream file;

	bool vflag = false;
	bool mciflag = false;
	bool sumflag = false;

	int tokCount = 0;
	int stringCount = 0;
	map<TType,int> counts;
	map<string,bool> allStrings;
	map<string,int> identCount;

	for(auto arg : args) {
		if(arg == "-v")
			vflag = true;
		else if(arg == "-mci")
			mciflag = true;
		else if(arg == "-sum")
			sumflag = true;
		else if(arg[0] == '-')  {
			cerr << "INVALID FLAG " << arg << endl;
			return 0;
		}
		else if(in != &cin) {
			cerr << "TOO MANY FILE NAMES" << endl;
			return 0;
		}
		else {
			file.open(arg);
			if(file.is_open() == false) {
				cerr << "UNABLE TO OPEN " << arg << endl;
				return 0;
			}
			in = &file;
		}
	}

	while((tok = getNextToken(in, &lineNumber)) != DONE && tok != ERR) {
		if(vflag)
			cout << tok << endl;

		++tokCount;

		if(tok == SCONST) {
			stringCount++;
			allStrings[ tok.GetLexeme() ] = true;
		}

		else if(tok == IDENT)
			identCount[ tok.GetLexeme() ]++;
	}

	if(tok == ERR) {
		cout << "Error on line " << lineNumber << " (" << tok.GetLexeme() << ")" << endl;
		return 0;
	}

	if(mciflag && identCount.size() > 0) {
    cout << "Most Common Identifier: ";

		// what is the most common identifier?
		// first, find the largest counter in the map
		int maxcnt = 0;
    for(auto it : identCount)
			if(it.second > maxcnt)
				maxcnt = it.second;

		// now, print all the identifiers with that length
		bool printed = false;
    for(auto it : identCount) {
			if(it.second != maxcnt)
				continue;

			if(printed)
				cout << ", ";

      printed = true;
			cout << it.first;
		}
		cout << endl;
	}

	if(sumflag) {
		cout << "Total lines: " << lineNumber << endl;
		cout << "Total tokens: " << tokCount << endl;

		if(tokCount > 0) {
			cout << "Total strings: " << stringCount << endl;

			if(stringCount > 0) {
				unsigned max_string_len = 0;
				for(auto string : allStrings) {
					if(string.first.length() > max_string_len)
						max_string_len = string.first.length();
				}
				cout << "Length of longest string: " << max_string_len << endl;
			}
		}
	}

	return 0;
}
