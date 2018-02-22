#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
  string foo("BarrBBB");

  int count = 0;

  for(auto c : foo)
    if(isupper(c))
      ++count;

  cout << count;
}
