#include <iostream>
#include <algorithm>
#include <string>
#include <ctype.h>
using namespace std;

struct PERSON {
  string name;
  string gender;
  unsigned int age;
};

PERSON get_data() {
  PERSON person;

  cout << "Enter the person's name: ";
  getline(cin, person.name);

  cout << "Enter the person's gender ('M' or 'F'): ";
  cin >> person.gender;

  cout << "Enter the person's age: ";
  cin >> person.age;

  return person;
}

void print_data(PERSON person) {
  cout << "Name: " << person.name;
  transform(person.gender.begin(), person.gender.end(), person.gender.begin(),::tolower);
  cout << "\nGender: " << person.gender;
  cout << "\nAge: " << person.age << "\n";
}
