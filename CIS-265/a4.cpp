/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 4
Due by 7/29/17
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
  int month, day, year;

  cout << "---Magic Date Program---\nEnter the month, day, and two-digit year "
          "(numerical)\n\nEnter month:\t\t";
  cin >> month;

  cout << "Enter day:\t\t";
  cin >> day;

  cout << "Enter two-digit year:\t";
  cin >> year;

  if ((month * day) == year) {
    cout << endl << month << "/" << day << "/" << year << " is a magic date.";
  } else {
    cout << endl << month << "/" << day << "/" << year << " is not a magic date.";
  }

  return 0;
}
