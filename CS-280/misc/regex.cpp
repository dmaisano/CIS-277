#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
  // const string s = "/home/toto/FILE_mysymbol_EVENT.DAT";
  // regex rgx(".*FILE_(\\w+)_EVENT\\.DAT.*");
  // smatch match;

  // if (regex_search(s.begin(), s.end(), match, rgx))
  //   cout << "match: " << match[1] << '\n';

  const string str = "   parse me.  I  dare you?  ";
  regex rgx("[\\w\\s]+"); // A-Za-z0-9_@./#&+-
  sregex_iterator iter(str.begin(), str.end(), rgx);
  sregex_iterator reg_end;

  for(; iter != reg_end; ++iter) {
    cout << "substring: " << iter->str() << "\tposition: " << iter->position() << endl;
  }
}
        