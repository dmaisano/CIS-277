/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 8
Due by 8/08/17
*/

#include <iostream>
using namespace std;

int main() {
  int speed, hours, distance;

  cout << "Enter the speed of a vehicle (in mph): ";
  cin >> speed;

  while (speed < 0) { // input validation for speed
    cout << "No negative values.\nEnter the speed of a vehicle (in mph): ";
    cin >> speed;
  }

  cout << "How many hours has the vehicle traveled: ";
  cin >> hours;

  while (hours < 1) { // input validation for time travelled
    cout << "Hours travelled must be greater than or equal to one.\nHow many "
            "hours has the vehicle traveled: ";
    cin >> hours;
  }

  cout << "\nHour\t\tDistance Traveled"; // distance is in miles (mi)
  cout << "\n---------------------------------";

  for (int i = 1; i <= hours; i++) { // loop to display the distance travelled per hour
    distance = (speed * i);          // the distance per iteration of the loop is equal
                                     // to the hour travelled times the speed

    cout << "\n" << i << "\t\t" << distance;
  }

  return 0;
}
