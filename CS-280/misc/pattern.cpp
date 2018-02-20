#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

int main() {
  vector<string> words = {};
  string foo = "this file has      sev3ral      Extra      words!";
  string::iterator iter = foo.begin();
  string tmp = "";
  string delim = "";
  int count;
  bool foundWord = false;
  bool nextWord = false; // look for next word

  for(auto c : foo) {
    if(!isspace(c)) {
      ++count;
      foundWord = true;
    }

    if(isspace(c) && foundWord && nextWord == false) {
      ++count;
      nextWord = true;
    }

    if(isspace(c) && foundWord == false && nextWord == true) {
      break;
    }
  };

  auto token = foo.substr(0, count);

  cout << count << endl << token;

  // for(auto c : foo) {
  //   if(!isspace(c)) {
  //     foundWord = true;
  //   }

  //   if(foundWord && nextWord == false) {
  //     tmp += c;
  //   }

  //   if(isspace(c) && foundWord) {
  //     tmp += c;
  //     nextWord = true;
  //     foundWord = false;
  //   }

  //   if(foundWord == true && nextWord == true) {
  //     words.push_back(tmp);
  //     tmp = c;
  //     nextWord = false;
  //     foundWord = true;
  //   }
  // }

  // for(string::iterator it = foo.begin(); it != foo.end(); ++it) {
  //   if(!isspace(*it)) {

  //   }
  // }

  // for(auto word : words) {
  //   for(auto c : word) {
  //     if(isspace(c))
  //       cout << "*";
  //     else if(!isspace(c))
  //       cout << c;
  //   }
  //   cout << endl;
  // }
}
