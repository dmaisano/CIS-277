#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
  const string s = "/home/toto/FILE_mysymbol_EVENT.DAT";
  regex rgx(".*FILE_(\\w+)_EVENT\\.DAT.*");
  smatch match;

  if (regex_search(s.begin(), s.end(), match, rgx))
    cout << "match: " << match[1] << '\n';
}
        