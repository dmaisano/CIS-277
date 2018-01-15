/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 4
Due by 7/29/17
*/

/*
Steps
1. Input:
    a. month
    b. day
    c. year

2. Processing:
    a. if(month * day == year) (do something)
    b. else (do something else)

3. Output:
    a. if(month * day == year)
        cout << "Magic date";

    b. else
        cout << "Not magic date";
*/

#include <iostream> 
#include <string>
using namespace std;

int main() {
    int month, day, year; // variable declaration

    cout << "---Magic Date Program---\nEnter the month, day, and two-digit year (numerical)\n\nEnter month:\t\t";
    cin >> month;

    cout << "Enter day:\t\t";
    cin >> day;

    cout << "Enter two-digit year:\t";
    cin >> year;

    if( (month * day) == year ) { // if the (month x day) is equal to the year, display that it is a magic date
        cout << "\n" << month << "/" << day << "/" << year << " is a magic date.";
    }
    else { // if it isn't, display that the data entered is not a magic date
         cout << "\n" << month << "/" << day << "/" << year << " is not a magic date.";
    }

    return 0;
}
