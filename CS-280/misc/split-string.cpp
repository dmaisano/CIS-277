#include<iostream>
#include<sstream>
#include<string>
// #include<cctype>
#include <ctype.h>
#include<vector>
#include<regex>
using namespace std;

vector<string> splitString(const string &str) {
  regex spaces("\\s(.*)");
  stringstream ss(str);
  string item;

  vector<string> res;

  while(ss >> item) {
    string temp = "";
    bool foundChar = false;

    // loops over each character in 'item'
    for(auto c : item) {
      // executes if any non-whitespace char is found
      if(!isspace(c)) {
        temp += c;
        foundChar = true;
      }

      // executes if any whitespace is found after the word/char
      if(isspace(c) && foundChar)
        break;
    }

    // appends word to the list
    res.push_back(temp);
  }

  return res;
}

string squish(string s) {
  if(s == "") {
    cout << "NO STRING PROVIDED" << endl;
    return "";
  }
  
  string res = "";
  auto items = splitString(s);

  for(auto item :  items)
    res += item + " ";

  res.pop_back(); // removes the trailing space at the end of the string
  return res;
}

int main() {
  // string test = "I-hate-doing-lab-reports-for-physics";
  string spaces = "     ahhhh  another word  done";

  vector<string> words;
  words = splitString(spaces);
  // for(auto const word : words)
  //   cout << word << endl;



  string res = squish(spaces);
  cout << res << endl << "Length: " << res.length() << endl;
}
