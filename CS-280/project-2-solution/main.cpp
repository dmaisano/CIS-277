/*
 * main.cpp
 *
 * CS280 - Fall 2017
 * Lexical Analyzer test engine
 */

#include <fstream>
using std::ifstream;

#include <map>
using std::map;

#include "projlex.h"
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int
main(int argc, char *argv[])
{
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

	for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
		if( arg == "-v" )
			vflag = true;
		else if( arg == "-mci" )
			mciflag = true;
		else if( arg == "-sum" )
			sumflag = true;
		else if( arg[0] == '-' ) {
			cerr << "INVALID FLAG " << arg << endl;
			return 0;
		}
		else if( in != &cin ) {
			cerr << "TOO MANY FILE NAMES" << endl;
			return 0;
		}
		else {
			file.open(arg);
			if( file.is_open() == false ) {
				cerr << "UNABLE TO OPEN " << arg << endl;
				return 0;
			}

			in = &file;
		}
	}

	while( (tok = getNextToken(in, &lineNumber)) != DONE && tok != ERR ) {
		if( vflag )
			cout << tok << endl;

		++tokCount;
		if( tok == SCONST ) {
			stringCount++;
			allStrings[ tok.GetLexeme() ] = true;
		}
		else if( tok == IDENT )
			identCount[ tok.GetLexeme() ]++;
	}

	if( tok == ERR ) {
		cout << "Error on line " << lineNumber << " (" << tok.GetLexeme() << ")" << endl;
		return 0;
	}

	if( mciflag && identCount.size() > 0 ) {
     	cout << "Most Common Identifier: ";
		// what is the most common identifier?
		// first, find the largest counter in the map
		int maxcnt = 0;
		for( auto it = identCount.begin(); it != identCount.end(); it++ )
			if( it->second > maxcnt )
				maxcnt = it->second;

		// now, print all the identifiers with that length
		bool printed = false;
		for( auto it = identCount.begin(); it != identCount.end(); it++ ) {
			if( it->second != maxcnt )
				continue;
			if( printed )
				cout << ", ";
         	printed = true;
			cout << it->first;
		}
		cout << endl;
	}

	if( sumflag ) {
		cout << "Total lines: " << lineNumber << endl;
		cout << "Total tokens: " << tokCount << endl;
		if( tokCount > 0 ) {
			cout << "Total strings: " << stringCount << endl;
			if( stringCount > 0 ) {
				unsigned maxSlen = 0;
				for( auto it = allStrings.begin(); it != allStrings.end(); it++ ) {
					if( it->first.length() > maxSlen )
						maxSlen = it->first.length();
				}
				cout << "Length of longest string: " << maxSlen << endl;
			}
		}
	}

	return 0;
}
