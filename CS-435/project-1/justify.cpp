#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

string wordWrap(vector<string> words, int width) {

  string wrappedText = "";

  string line = "";

  for (auto word : words) {
    int len = line.length();

    if (line.length() == width) {
      cout << "owo\t" << word;
      wrappedText += line + "\n";
      line = "";
      // line = (word.length() + 1 < width) ? word + "_" : word;
    }

    if (line == "") {
      cout << "\tuwu\t" << word << endl;
      line += word + "_";
      // line += (word.length() + 1 < width) ? word + "_" : word;
      continue;
    }

    if (len + word.length() + 1 < width) {
      line += word + "_";
    } else if (len + word.length() < width) {
      line += word;
    } else {
      for (int i = len; i < width; i++) {
        line += "_";
      }
    }
  }

  // for (auto word : words) {
  // int lineLength = line.length();

  // if (lineLength == width) {
  //   wrappedText += line + "\n";

  //   line = (lineLength + word.length() + 1 < width) ? word + "_" : word;
  // }

  // cout << "line length: " << lineLength << "\tword: " << word << endl;

  // if (lineLength + word.length() < width) {
  //   line += (lineLength + word.length() + 1 < width) ? word + "_" : word;
  // } else {
  //   for (int i = lineLength; i < width; i++) {
  //     line += "_";
  //   }
  // }
  // }

  return wrappedText;
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

  cout << res << endl;

  // for (auto line : res) {
  //   cout << line << endl;
  // }
}
