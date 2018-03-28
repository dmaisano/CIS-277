#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
using namespace std;

const int IN = 0;
const int OUT = 1;
const int NSTATS = 2;

int
main(int argc, char *argv[])
{
	bool quiet = false;
	bool squish = false;
	bool censor = false;
	bool pstats = false;
	bool length = false;

	istream* in = &cin;
	ifstream infile;

	for( int i=1; i<argc; i++ ) {
		string arg(argv[i]);
		if( arg[0] == '-' ) {
			if( arg == "-q" )
				quiet = true;
			else if( arg == "-s" )
				squish = true;
			else if( arg == "-c" )
				censor = true;
			else if( arg == "-p" )
				pstats = true;
			else if( arg == "-l" )
				length = true;
			else {
				cout << arg << " INVALID FLAG" << endl;
				return 0;
			}
		}
		else {
			if( in != &cin ) {
				cout << "TOO MANY FILES" << endl;
				return 0;
			}
			infile.open(arg);
			if( infile.is_open() == false ) {
				cout << arg << " CANNOT OPEN" << endl;
				return 0;
			}
			in = &infile;
		}
	}

	if( (squish || censor) && quiet ) {
		cout << "CONFLICTING FLAGS" << endl;
     	return 0;
	}

	bool in_word = false;
	char input;
	string word, spaces;
	int charcnt[NSTATS] = {0,0};
	int newlines[NSTATS] = {0,0};

	int wordcnt[NSTATS] = {0,0};
	int goodcnt[NSTATS] = {0,0};
	int realcnt[NSTATS] = {0,0};
	int capcnt[NSTATS] = {0,0};
	int acrocnt[NSTATS] = {0,0};
	bool goodword = true, realword = true, capword = false, acronym = true;

	unsigned int wordlen = 0;
	map<string,bool> longwords;
	unsigned int goodlen = 0;
	map<string,bool> goodwords;
	unsigned int reallen = 0;
	map<string,bool> realwords;

	while( in->get(input) ) {
		charcnt[IN]++;
		if( input == '\n' )
			newlines[IN]++;

		if( in_word == false ) {
			if( isspace(input) ) {
				spaces += input;
			}
			else {
				if( squish ) {
                 	if( spaces.length() > 1 ) {
 						char lastws = spaces.back();
 						spaces = lastws;
                    }
				}
             	if( !censor || (censor && realword) ) {
				for( size_t i=0; i<spaces.length(); i++) {
					if( quiet == false ) {
						cout << spaces[i];
						if( spaces[i] == '\n' )
							newlines[OUT]++;
						charcnt[OUT]++;
					}
				}
                }
				spaces.clear();

				in_word = true;
				goodword = true, realword = true, capword = false, acronym = true;
				word = input;
				if( isalpha(input) && isupper(input) ) {
					capword = true;
                 	capcnt[IN]++;
                }
				if( !isalnum(input) ) goodword = realword = false;
				if( goodword && isdigit(input) ) realword = false;
				if( acronym && !isupper(input) ) acronym = false;
			}
		}
		else {
			// in a word
			if( isspace(input) ) {
				in_word = false;
				spaces = input;

				wordcnt[IN]++;
                 	if( word.length() >= wordlen ) {
                    	if( word.length() > wordlen ) {
                        	longwords.clear();
                         	wordlen = word.length();
                        }
                    	longwords[word] = true;
                    }
				if( goodword ) {
                	goodcnt[IN]++;
                 	if( word.length() >= goodlen ) {
                    	if( word.length() > goodlen ) {
                        	goodwords.clear();
                         	goodlen = word.length();
                        }
                    	goodwords[word] = true;
                    }
                }
				if( realword ) {
                	realcnt[IN]++;
                 	if( word.length() >= reallen ) {
                    	if( word.length() > reallen ) {
                        	realwords.clear();
                         	reallen = word.length();
                        }
                    	realwords[word] = true;
                    }
                }
				if( acronym ) {
                	acrocnt[IN]++;
                 	//cout << "ACRO " << word << endl;
                }
				if( quiet == false && (!censor || (censor && realword)) ) {
					cout << word;
					charcnt[OUT] += word.length();
					wordcnt[OUT]++;
 					if( goodword ) goodcnt[OUT]++;
					if( realword ) realcnt[OUT]++;
					if( acronym ) acrocnt[OUT]++;
                	if( capword ) capcnt[OUT]++;
				}
				word.clear();
			}
			else {
				word += input;
				if( !isalnum(input) ) goodword = realword = false;
				if( goodword && isdigit(input) ) realword = false;
				if( acronym && !isupper(input) ) acronym = false;
			}
		}
	}

	// flush out whatever i was in the middle of
	if( in_word ) {
		wordcnt[IN]++;
                 	if( word.length() >= wordlen ) {
                    	if( word.length() > wordlen ) {
                        	longwords.clear();
                         	wordlen = word.length();
                        }
                    	longwords[word] = true;
                    }
		if( quiet == false && (!censor || (censor && realword)) ) {
			cout << word;
			charcnt[OUT] += word.length();
			wordcnt[OUT]++;
			if( goodword ) goodcnt[OUT]++;
			if( realword ) realcnt[OUT]++;
			if( acronym ) acrocnt[OUT]++;
            if( capword ) capcnt[OUT]++;
		}
	}
	else {
		if( squish ) {
        	if( spaces.length() > 1 ) {
 				char lastws = spaces.back();
 				spaces = lastws;
            }
		}
        if( !censor || (censor && realword) ) {
		for( size_t i=0; i<spaces.length(); i++) {
			if( quiet == false ) {
				cout << spaces[i];
				if( spaces[i] == '\n' )
					newlines[OUT]++;
				charcnt[OUT]++;
			}
		}
        }
	}

	if( pstats ) {
		cout << "Characters " << charcnt[IN] << " in " << charcnt[OUT] << " out" << endl;
		cout << "Lines " << newlines[IN] << " in " << newlines[OUT] << " out" << endl;
		cout << "Words " << wordcnt[IN] << " in " << wordcnt[OUT] << " out" << endl;
		cout << "Goodwords " << goodcnt[IN] << " in" << endl;
		cout << "Realwords " << realcnt[IN] << " in" << endl;
		cout << "Capwords " << capcnt[IN] << " in" << endl;
		cout << "Acronyms " << acrocnt[IN] << " in" << endl;
	}
 
 	if( length ) {
  		if( longwords.size() > 0 ) {
        	cout << "Word (length " << wordlen << "): ";
        	for( auto it = longwords.begin(); it != longwords.end(); it++ ) {
            	if( it != longwords.begin() )
                	cout << ", ";
            	cout << it->first;
            }
        	cout << endl;
        }
  		if( goodwords.size() > 0 ) {
        	cout << "Goodword (length " << goodlen << "): ";
        	for( auto it = goodwords.begin(); it != goodwords.end(); it++ ) {
            	if( it != goodwords.begin() )
                	cout << ", ";
            	cout << it->first;
            }
        	cout << endl;
        }
  		if( realwords.size() > 0 ) {
        	cout << "Realword (length " << reallen << "): ";
        	for( auto it = realwords.begin(); it != realwords.end(); it++ ) {
            	if( it != realwords.begin() )
                	cout << ", ";
            	cout << it->first;
            }
        	cout << endl;
        }
 	}

	return 0;
}
