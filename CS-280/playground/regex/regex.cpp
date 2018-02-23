#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

vector<string> patternSearch(const string str, const regex pattern) {
  sregex_iterator it(str.begin(), str.end(), pattern), reg_end;
  vector<string> words;

  // reg_end == empty/null iterator
  for(; it != reg_end; ++it) {
    words.push_back(it->str());

    // visibly shows whitespace in output
    // for(auto c : it->str()) {
    //   if(c == ' ')
    //     cout << '*';
    //   else
    //     cout << c;
    // }
    // cout << endl;
  }

  return words;
}

int main() {
  vector<string> sampleTXT = {
    "this file has      sev3ral      Extra      words!",
    "that the censors really, really, need to catch!",
    "fix",
    "yes indeed"
  };
  string sample1 = "   parse   me  I   dare  you  ";
  string sample2 = "The the cow jumped over the the moon";
  const regex re(R"([\s]*[\w|.!?]+[\s]*)");
  sregex_iterator it(sample1.begin(), sample1.end(), re), reg_end;

  // auto words = patternSearch(sample3, re);
  // for(auto word : words)
  //   cout << word << endl;

  for(auto str : sampleTXT) {
    auto words = patternSearch(str, re);
    
    for(auto word : words)
      cout << word << "\t";

    cout << endl;
  }
}
