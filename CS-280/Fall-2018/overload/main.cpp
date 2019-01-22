#include <iostream>
using namespace std;

class Numberr {
private:
  int value;

public:
  Numberr(int n) { value = n; }

  friend ostream &operator<<(ostream &out, const Numberr &n);

  Numberr operator+(Numberr const &obj) { return Numberr(value + obj.value); }
};

ostream &operator<<(ostream &out, const Numberr &n) { return out << n.value; }

int main() {

  Numberr foo(10), bar(20), baz(30);

  Numberr sum1 = foo + bar;

  Numberr sum2 = foo + bar + baz; // sum1 + baz

  cout << sum1 << endl;

  cout << sum2 << endl;

  return 0;
}
