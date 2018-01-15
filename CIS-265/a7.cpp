/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 7
Due by 8/08/17
*/

/*
Steps
1. Input:
    a. userInt

2. Processing:
    a. input validation for userInt (no negative values).
    b. sum = userInt (input from user).
    c. while loop to get the sum of the numbers

3. Output:
    a. Total sum of the numbers
*/

#include <iostream>
using namespace std;

int main() {
  int userInt = 0;
  int sum = 0;
  int count = 0;

  cout << "Enter a positive integer: ";
  cin >> userInt;

  while(userInt < 0) {
    cout << "Number entered cannot be negative.\nEnter a positive integer: ";
    cin >> userInt;
  }

  sum += userInt;

  while(count != userInt) {
    sum += count;

    count++;
  }

  cout << "Sum of numbers: " << sum;
  
  return 0;
}
