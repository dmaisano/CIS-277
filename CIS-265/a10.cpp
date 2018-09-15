/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 10
Due by 8/08/17
*/

#include <iostream>
using namespace std;

int main() {
  int sales[5];

  for (int i = 0; i < 5; i++) {
    cout << "Enter the sales for store " << i + 1 << ": $";
    cin >> sales[i];
  }

  cout << "\nSALES BAR CHART\n(each * = $100)\n---------------";

  for (int x = 0; x < 5; x++) {
    int ast = sales[x] / 100;

    cout << "\nSales for Store " << x + 1 << ": ";

    for (int y = 0; y < ast; y++) {
      cout << "*";
    }
  }

  return 0;
}
