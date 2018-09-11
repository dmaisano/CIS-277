#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> findLargest(const vector<string> words) {
  vector<string> res;
  int size = 0;

  for (auto word : words) {
    if (word.length() > size)
      size = word.length();
  }

  for (auto word : words) {
    if (word.length() == size)
      res.push_back(word);
  }

  cout << "words: ";

  for (int i = 0; i < res.size(); i++) {
    if (i < res.size() - 1)
      cout << res[i] << ", ";
    else
      cout << res[i];
  }

  return res;
}

int main() {
  vector<string> wordlist = {"this", "has", "sev3ral", "censors"};

  auto res = findLargest(wordlist);
}
