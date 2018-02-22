#include <iostream>
#include <string>
#include <regex>
using namespace std;

void printPattern(const string str, const regex pattern) {
  sregex_iterator it(str.begin(), str.end(), pattern), reg_end;

  // reg_end == empty/null iterator
  for(; it != reg_end; ++it) {
    // cout << it->str() << endl;

    // visibly shows whitespace in output
    for(auto c : it->str()) {
      if(c == ' ')
        cout << '*';
      else
        cout << c;
    }
    cout << endl;
  }
}

int main() {
  string sample1 = "   parse   me  I   dare  you  ";
  string sample2 = "The the cow jumped over the the moon";
  const regex re(R"([\s]*[\w]+[\s]*)");
  sregex_iterator it(sample1.begin(), sample1.end(), re), reg_end;

  printPattern(sample1, re);
}
