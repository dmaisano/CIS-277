#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<string> v = {"Hello, ", " Cruel ", "World!"};
  string str;
  str = accumulate(v.begin(), v.end(), str);

  cout << str;
}
