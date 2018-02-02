#ifndef LEX_H
#define LEX_H
#include<iostream>
#include<sstream>
#include<string>
#include <ctype.h>
#include<vector>
using namespace std;

class Lex {
public:
  static vector<string> splitString(const string str) {
    stringstream ss(str);
    string item;

    // returns list of words
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

  static string squish(string s) {
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
};

#endif 
