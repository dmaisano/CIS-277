#ifndef PATTERN_MATCHER_H
#define PATTERN_MATCHER_H
using namespace std;

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <algorithm> // count()
using namespace std;

class PatternMatcher {
public:
  static void Parse(const string fileName, const set<string> parserFlags) {
    // brace yourself
    enum wordMode { unknown, wordish, spaceish };
    const int IN = 0, OUT = 1;
    unsigned int wordlen = 0, goodlen = 0, reallen = 0;
    map<string, bool> longwords, goodwords, realwords;

    map<string, bool> wordOptions = {
      { "goodword", true  },
      { "realword", true  },
      { "capword",  true },
      { "acronym",  true  }
    };

    // ie. stats["charCount"][OUT] == stats["charCount"][1]
    map<string, vector<int>> stats = {
      { "charCount", {0, 0} },
      { "lineCount", {0, 0} },
      { "wordCount", {0, 0} },
      { "goodCount", {0, 0} },
      { "realCount", {0, 0} },
      { "capCount",  {0, 0} },
      { "acroCount", {0, 0} }
    };

    // contains the number of words meeting the criteria
    map<string, int> lengthMode = {
      { "words",     0 },
      { "goodwords", 0 },
      { "realwords", 0 },
    };

    istream* in = &cin;
    ifstream file(fileName);
    in = &file;
    wordMode mode = unknown;
    string word, spaces;
    char c;

    while(in->get(c)) {
      ++stats["charCount"][IN];

      if(c == '\n') ++stats["lineCount"][IN];

      if(mode == unknown || mode == spaceish) {
        if(isspace(c))
          spaces += c;
        
        else {
          if(inFlags(parserFlags, "-s")) {
            if(spaces.length() > 1) {
              char lastws = spaces.back();
 						  spaces = lastws;
            }
          }

          if(!inFlags(parserFlags, "-c") || (inFlags(parserFlags, "-c") && wordOptions["realword"])) {
            for(auto space : spaces) {
              if(!inFlags(parserFlags, "-q")) {
                cout << space;
                if(space == '\n') ++stats["lineCount"][OUT];
                ++stats["charCount"][OUT];
              }
            }
          }

          spaces.clear();
          mode = wordish;;
          reset_word_options(wordOptions);
          word = c;

          if( isalpha(c) && isupper(c) ) {
            wordOptions["capword"] = true;
            ++stats["capCount"][IN];
          }
          if(!isalnum(c))
            wordOptions["goodword"] = wordOptions["realword"] = false;
          if(wordOptions["goodword"] && isdigit(c) )
            wordOptions["realword"] = false;
          if(wordOptions["acronym"] && !isupper(c) )
            wordOptions["acronym"] = false;
        }
      }

      // we found a word
      else if(mode == wordish) {
        if(isspace(c)) {
          mode = spaceish;
          spaces = c;
          ++stats["wordCount"][IN];

          if(word.length() >= wordlen) {
            if(word.length() > wordlen ) {
              longwords.clear();
              wordlen = word.length();
            }
            longwords[word] = true;
          }

          if(wordOptions["goodword"]) {
            ++stats["goodCount"][IN];
            if(word.length() >= goodlen) {
              if(word.length() > goodlen) {
                goodwords.clear();
                goodlen = word.length();
              }
              goodwords[word] = true;
            }
          }
          
          if(wordOptions["realWord"]) {
            ++stats[]
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
  }

private:
  // resets the wordOptions back to it's default state
  static void reset_word_options(map<string, bool>& wordOptions) {
    wordOptions = {
      { "goodword", true  },
      { "realword", true  },
      { "capword",  true  },
      { "acronym",  true  }
    };
  }
};

// returns true if the flag provided is found
extern bool inFlags(const set<string> flags, string arg) {
  for(auto flag : flags)
    if(flag == arg)
      return true;
  return false;
}

// returns a vector of strings per line
extern vector<vector<string>> parseFile() {
  vector<vector<string>> parsedFile;

  return parsedFile;
}

#endif 
