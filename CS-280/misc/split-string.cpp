#include<iostream>
#include<sstream>
#include<string>
// #include<cctype>
#include<vector>
using namespace std;

vector<string> splitString(const string &str, const char delim) {
  stringstream ss(str);
  string item;

  vector<string> res;

  while(getline(ss, item, delim))
    res.push_back(item);

  return res;
}

int main() {
  string test = "I-hate-doing-lab-reports-for-physics";

  vector<string> words;

  words = splitString(test, '-');

  for(int i = 0; i < words.size(); i++) {
    cout << words[i];

    if(i < words.size() - 1)
      cout << endl;
  }
}
