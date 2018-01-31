#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
using namespace std;

bool isOdd(int num) {
  return (num % 2) == 1;
};

int main() {
  int sampleArray[] = { 2, 4, 6, 8, 10 };
  int* f;
  int size = sizeof(sampleArray) / sizeof(*sampleArray);

  // find()
  f = find (sampleArray, sampleArray+5, 8);
  cout << *f; // 8

  vector<int> vect;
  vect.push_back(12);
  vect.push_back(14);
  vect.push_back(15);
  vect.push_back(16);
  vect.push_back(18);
  vect.push_back(20);

  // find_if()
  // anonymous / lambda functions are so beautiful!!
  vector<int>::iterator iter = find_if(vect.begin(), vect.end(), [](int num) {
    return (num % 2) == 1;
  });

  cout << *iter; // 
}
