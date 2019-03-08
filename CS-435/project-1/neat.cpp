#include <iostream>
#include <regex>
#include <string>
using namespace std;

void neat(int maxLength) {
  string result;

  int currentLength = 0;
  int totalCost = 0;

  string word;
  while (cin >> word) {
    int wordLength = word.length();

    if (wordLength <= maxLength) {
      result += word;

      if (result.length() % maxLength == 0) {
        result += '\n';
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int lineLength = 60;

  // check if arg is int
  if (argv[1] && regex_match(argv[1], regex("[0-9]+"))) {
    lineLength = stoi(argv[1]);
  }

  neat(lineLength);
}
