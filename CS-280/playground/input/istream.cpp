#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <regex>
using namespace std;

string getTrimmedLine(istream *in);
string trimWS(const string str);
bool isWS(const string str);

int main() {
  // istream* in = &cin;
  // ifstream file("../../project2/p2cases/good.txt");
  ifstream file("./sample.txt");
  string line;

  while(getline(file, line))
    if(!isWS(line))
      cout << trimWS(line) << endl;
}

string getTrimmedLine(istream *in) {
  string currentLine, tmp;
  char c;

  getline(*in, currentLine);

  if(!isWS(currentLine))
    return trimWS(currentLine);

  return "";

  // while(in->get(c)) {
  //   if(c != '\n')
  //     currentLine += c;
  //   else if(c == '\n') {
  //     if(isWS(currentLine))
  //       continue;

  //     auto trimmedLine = trimWS(currentLine);
  //     cout << trimmedLine << endl;
  //     currentLine = "";
  //   }
  // }
}

string trimWS(const string str) {
  string trimmedLine, word;
  istringstream ss(str);

  while(ss >> word)
    trimmedLine += (word + " ");

  trimmedLine.pop_back(); // remove extra whitespace;

  return trimmedLine;
}

bool isWS(const string str) {
  for(auto c : str) {
    if(isspace(c))
      continue;
    else
      return false;
  }

  return true;
}
