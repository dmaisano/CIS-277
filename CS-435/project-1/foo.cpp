#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<string> wordWrap(vector<string> words, int width) {
  vector<string> wrappedLines;
  bool done = false;
  int wordIndex = 0;
  int lineIndex = 0;

  string line = "";

  for (int i = 0; i <= 4; i++) {
    line += "owo";

    if (i % 2 == 0) {
      line += "uwu";
    }

    if (i == 4) {
      wrappedLines.push_back(line + "\n");
      line = "";

      cout << line;
    }
  }

  // for (auto word : words) {
  //   int len = line.length();
  //   // cout << word << "\tline length: " << line.length() << "\t" << line <<
  //   // endl;

  //   if (len == width) {
  //     wrappedLines.push_back(line + "\n");
  //     line = "";
  //     cout << "line: " << line << "\tlength: " << len << endl;
  //     lineIndex++;
  //   }

  //   if (len + 1 < width) {
  //     line += word + "_";
  //   } else if (len < width) {
  //     line += word;
  //   } else {
  //     for (int i = len; i <= width; i++) {
  //       line += "_";
  //     }
  //   }
  // }

  return wrappedLines;
}

int main(int argc, char *argv[]) {
  int maxWidth = 60;

  // check if arg is int
  if (argv[1] && regex_match(argv[1], regex("[0-9]+"))) {
    maxWidth = stoi(argv[1]);
  }

  vector<string> words;

  string word;
  while (cin >> word) {
    words.push_back(word);
  }

  auto res = wordWrap(words, maxWidth);

  for (auto line : res) {
    cout << line << endl;
  }
}
