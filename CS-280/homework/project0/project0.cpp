// Domenico Maisano
// CS280 - 008

#include <iostream>
#include <string.h>
using namespace std;

struct params {
  string s;
  int value;
};

int main(int argc, char *argv[]) {
  params sm = { "small", 5 };
  params md = { "medium", 10 };
  params lg = { "large", 20 };

  if(argc <= 1) {
    cout << "MISSING SIZE" << endl;
    exit;
  }

  for(int i = 1; i < argc; i++) {
    if(argv[1] == sm.s || argv[1] == md.s || argv[1] == lg.s) {
      if(i > 1 && strlen(argv[i]) >= sm.value && argv[1] == sm.s)
        cout << argv[i] << "\n";

      else if(i > 1 && strlen(argv[i]) >= md.value && argv[1] == md.s)
        cout << argv[i] << "\n";

      else if(i > 1 && strlen(argv[i]) >= lg.value && argv[1] == lg.s)
        cout << argv[i] << "\n";
    }

    else {
      cout << argv[1] << " NOT A VALID SIZE" << endl;
    }
  }
}
