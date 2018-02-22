#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <regex>
using namespace std;

int main() {
  string fileName = "./second.txt";
  ifstream file(fileName);
  string parsedLine, word;
  bool foundWS, foundWord;

  string str = "      Parse   me\\0";
  int size = str.size() - 1;

  for(int i = 0; i <= size; i++) {
    char c = str[i];

    // if an empty line
    if(str == "\n" || str.empty()) {
      cout << "\n";
      exit(0);
    }

    // if any whitespace is found at the start of the line
    if(word == "" && isspace(c) && !foundWS && !foundWord) {
      word += c;
      foundWS = true;
    }

    // if a word is found
    if(!isspace(c) && !foundWS) {
      word += c;
      foundWord = true;
    }

    // appends the whitespace after a word
    else if(isspace(c) && foundWord) {
      word += c;
      foundWord = false;
      foundWS = true;
    }

    // if a word is found after the trailing whitespace of the previous word
    else if(!isspace(c) && !foundWord && foundWS) {
      parsedLine += word;
      word = c;
      foundWord = true;
      foundWS = false;
    }

    // if the last word is found
    if(i == size)
      parsedLine += word;
  }

  cout << parsedLine;

  file.close();
}
