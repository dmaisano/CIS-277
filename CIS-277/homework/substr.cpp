#include <iostream>
#include <string>
#include <vector>
using namespace std;

void menu();
bool fmsSubstr(string);
void pushChar(vector<char>&, char);

int main() {
  menu();

  cout << "\n\n";
  return 0;
}

void menu() {
  bool restart;

  do {
    vector<char> vect; // vector to hold the binary string (only 1s and 0s)
    string input; // string for the user input

    cout << "Enter a string: ";
    cin >> input;

    // converts the string to a character array to iterate over
    const char* charArray = input.c_str();

    // iterates through each character from the user's input
    for(int i = 0; i < input.length(); ++i) {
      switch(charArray[i]) {
        case '0': // if the current character is '0', push it to the vector
          pushChar(vect, charArray[i]);
          break;

        case '1': // if the current character is '1', push it to the vector
          pushChar(vect, charArray[i]);
          break;
        
        // the default case resumes the iterations of the loop and is run when the current character is neither a 0 or 1
        default: 
          continue;
      }
    }

    // converts the vector of characters to a string
    string str(vect.begin(), vect.end());

    // the conditional executes if a valid substring is found
    if(fmsSubstr(str))
      cout << input << " contains a valid substring of '1101'!";


    // the conditional executes if a valid substring is not found
    else
      cout << input << input << " does not contain a valid substring of '1101'!";

    cout << "\nRestart program?\n1 = YES\n2 = NO\nEnter choice: ";
    cin >> restart;

  } while(restart == 1);
}

// pushes the character to the char vector by reference without needing to specify a return type
void pushChar(vector<char>& vect, char c) {
  if(c == '0' || c == '1')
    vect.push_back(c);
}

// function to validate the contents of the string to determine if it contains the substring '1101'
bool fmsSubstr(string str) {
  if(str.find("1101") != string::npos)
    return true;
  
  return false;
}
