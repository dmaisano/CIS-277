#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  istringstream ss("hello  ");
  string word;

  ss >> word;
  int count = 0;

  for (auto c : word) {
    cout << c;
    ++count;
  }

  cout << endl << "chars: " << count;
}
