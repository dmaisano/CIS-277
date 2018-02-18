#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
  string s = "foo bar  baz";
  regex e("\\s+");
  regex_token_iterator<string::iterator> i(s.begin(), s.end(), e, -1);
  regex_token_iterator<string::iterator> end;
  while (i != end)
    cout << " [" << *i++ << "]";
}
