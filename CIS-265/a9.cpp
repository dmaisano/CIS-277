/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 9
Due by 8/08/17
*/

/*
Steps
1. Input:
    a. numYears
    b. rainFall    // per month of the year

2. Processing:
    a. input validation for numYears (no values less than 1).
    b. for loop to iterate per year in the numYears
    c. input validation for rainFall (no negative values).
    d. add the rainFall onto the value of the total_rainFall
    e. avg_rainFall = total_rainFall / (numYears * 12months);

3. Output:
    a. Total number of months
    b. Total amount of rainfall in inches
    c. Average rainfall per month in inches
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
      cout << "Enter the amount of rainfall (in inches) for year " << year
           << " month " << month << ": ";
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
  cout << "\nAverage Rainfall per month for " << numYears
       << " year(s): " << avg_rainFall << " inches";

  return 0;
}
