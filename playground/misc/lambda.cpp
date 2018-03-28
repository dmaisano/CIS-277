#include <iostream>
using namespace std;

int main() {
  auto saySomething = [](string phrase = "") {
    cout << phrase;
  };

  saySomething("taco cat");
  
  return 0;
}
