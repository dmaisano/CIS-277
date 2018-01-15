/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 10
Due by 8/08/17
*/

/*
Steps
1. Input:
    a. sales for each of the five stores

2. Processing:
    a. ast = the sales of a store / 100
    // (ex) sales = 500, sales / 100 = 5
    // five asterisks

3. Output:
    a. SALES BAR CHART
    b. (each * = $100)
    c. Sales for Store n: *****
*/

#include <iostream>
using namespace std;

int main() {
  int sales[5];

  for(int i = 0; i < 5; i++) {
    cout << "Enter the sales for store " << i + 1 << ": $";
    cin >> sales[i]; 
  }

  cout << "\nSALES BAR CHART\n(each * = $100)\n---------------";

  for(int x = 0; x < 5; x++) {
    int ast = sales[x] / 100;

    cout << "\nSales for Store " << x + 1 << ": ";

    for(int y = 0; y < ast; y++) {
      cout << "*";
    }
  }
  
  return 0;
}
