#include <iostream>
#include <string>
#include <fstream>
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
