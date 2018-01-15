/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 2
Due by 7/18/17
*/

/*
Steps
1. Input:
    -none

2. Processing:
    a. total = east_coast_sales * percentage;

3. Output:
    a. total sales generasted // which has a value of 2,852,000    2.852 million
*/

#include <iostream>
#include <iomanip> // used for setprecision to remove the trailing decimal places
using namespace std;

int main() {
    double east_coast_sales = 4.6E6, // $4.6 million
           percentage = 0.62,
           total = 0;

    total = east_coast_sales * percentage;

    cout << "Total sales generated from East Coast sales division: $" << fixed << setprecision(0) << total;
    // fixed removes scientific notation from the double value, setprecision(0) removes decimal places from the output
        
    return 0;
}
