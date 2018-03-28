#include <iostream>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

int main () {
  // token == some word
  map<string, vector<string>> token;
  
  token["abc"] = {"Hello", "World"};
  token["123"] = {"Foo", "Bar"};

  // works as such
  // token["abc"][0] = "Hello"

  for(auto it : token)
    for(auto value : it.second)
      cout << "key: " << it.first << "\tvalue: " << value << endl;
}
