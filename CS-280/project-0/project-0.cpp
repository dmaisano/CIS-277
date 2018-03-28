/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* project-0.cpp
*/


#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

struct params {
  string s;
  int value;
};

int main(int argc, char *argv[]) {
  params sm = { "small",  5  };
  params md = { "medium", 10 };
  params lg = { "large",  20 };

  vector<params> v = { sm, md, lg };

  if(argc <= 1) {
    cout << "MISSING SIZE" << endl;
    exit;
  }

  for(int i = 1; i < argc; i++) {
    // executes if the first arg is the string "small", "medium", or "large"
    if(argv[1] == sm.s || argv[1] == md.s || argv[1] == lg.s) {
      for(auto param : v)
        if(strlen(argv[i]) >= param.value && argv[1] == param.s)
          cout << argv[i] << "\n";
    }

    else {
      cout << argv[1] << " NOT A VALID SIZE" << endl;
    }
  }
}
