#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool fmsSubstr(string);
void pushChar(vector<char>&, char);

int main() {
  vector<char> vect;
  string input;

  cout << "Enter a string: ";
  cin >> input;

  const char* charArray = input.c_str();

  for(int i = 0; i < input.length(); ++i) {
    switch(charArray[i]) {
      case '0':
        pushChar(vect, charArray[i]);
        break;

      case '1':
        pushChar(vect, charArray[i]);
        break;
      
      default:
        continue;
    }
  }

  string str(vect.begin(), vect.end());

  cout << "\n" << fmsSubstr(str);

  if(fmsSubstr(str))
    cout << input << " is a valid substring!";

  else
    cout << input << input << " is not a valid substring!";

  cout << "\n\n";
  
  return 0;
}

void pushChar(vector<char>& vect, char c) {
  if(c == '0' || c == '1')
    vect.push_back(c);
}

bool fmsSubstr(string str) {
  if(str.find("1101") != string::npos)
    return true;
  
  return false;
}
