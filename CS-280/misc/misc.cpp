#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <map>
#include <vector>
using namespace std;

int main() {
  string fileName = "./second.txt";

  ifstream file(fileName);

  string res = "";

  char c;

  // loop through each character in the file
  while(file.get(c))
    if(c == '\n')
      cout << "\\n\n";
    
    else
      cout << c;

  file.close();
}
