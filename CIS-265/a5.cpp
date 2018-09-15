/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 5
Due by 7/29/17
*/

#include <iostream>
using namespace std;

int main() {
  int seconds, days, hours, minutes;

  cout << "---Time Calculator Program---\nEnter the number of seconds:\t";
  cin >> seconds;

  days = seconds / 86400; // calculation for number of days using the value of seconds

  // calculation for number of hours, seconds % days will return remainder
  // which will be divided by 3600, returning the number of hours
  hours = (seconds % 86400) / 3600;

  // calculation for number of minutes, seconds % hours will return remainder
  // which will be divided by 60, returning the number of minutes
  minutes = (seconds % 3600) / 60;

  // code will be executed if numSeconds is less than a minute
  if (seconds < 60) {
    cout << "Seconds entered: " << seconds;
    cout << "\nTry running the program again and entering more than 60 "
            "seconds.\n\n";
  }

  // code will be executed if numSeconds is grater than or equal to a minute and
  // less than an hour
  else if (seconds >= 60 && seconds < 3600) {
    cout << "Seconds entered: " << seconds << " = " << minutes << " minute(s).";
  }

  // code will be executed if numSeconds is grater than or equal to an hour and
  // less than a day
  else if (seconds >= 3600 && seconds < 86400) {
    cout << "Seconds entered: " << seconds << " = " << hours << " hour(s), and " << minutes << " minute(s).";
  }

  // code will be executed by default if numSeconds greater than or equal to a
  // day (86400 seconds)
  else {
    cout << "Seconds entered: " << seconds << " = " << days << " day(s), " << hours << " hour(s), and " << minutes
         << " minute(s).";
  }

  return 0;
}
