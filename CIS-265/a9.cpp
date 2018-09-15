/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 9
Due by 8/08/17
*/

#include <iostream>
using namespace std;

int main() {
  int numYears;
  int rainFall, total_rainFall = 0, avg_rainFall;

  cout << "Average Rainfall Program\nEnter the number of years to calculate "
          "the average rainfall: ";
  cin >> numYears;

  while (numYears < 1) { // input validation for numYears
    cout << "Number of years cannot be negative.\nEnter the number of years to "
            "calculate the average rainfall: ";
    cin >> numYears;
  }

  for (int year = 1; year <= numYears; year++) {
    for (int month = 1; month <= 12; month++) {
      cout << "Enter the amount of rainfall (in inches) for year " << year << " month " << month
           << ": ";
      cin >> rainFall;

      while (rainFall < 0) { // input validation for rainFall
        cout << "Value of rainfall cannot be negative.\nEnter the amount of "
                "rainfall (in inches) for year "
             << year << " month " << month << ": ";
        cin >> rainFall;
      }

      total_rainFall += rainFall; // add amount of rainfall to the total
    }
  }

  avg_rainFall = total_rainFall / (numYears * 12);

  cout << "Number of months: " << numYears * 12;
  cout << "\nTotal Rainfall: " << total_rainFall << " inches";
  cout << "\nAverage Rainfall per month for " << numYears << " year(s): " << avg_rainFall
       << " inches";

  return 0;
}
