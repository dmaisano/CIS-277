/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 6
Due by 7/29/17
*/

#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int fee = 10; // $10 monthly bank fee
  double initialBalance, numChecks, charges;

  cout << "Enter the beginning balance: $";
  cin >> initialBalance;

  while (initialBalance < 0) { // input validation
    cout << "\nAccount is overdawn.\nEnter the beginning balance: $";
    cin >> initialBalance;
  }

  cout << "Enter the number of checks written: ";
  cin >> numChecks;

  while (numChecks < 0) { // input validation
    cout << "\nNumber of checks written cannot be negative.\nEnter the number "
            "of checks written: ";
    cin >> numChecks;
  }

  charges = fee; // the initial charge is set to the $10 required monthly fee

  if (initialBalance < 400) { // if the beginning balance is less than $400, add a $15 fee
    charges += 15;
  }

  if (numChecks < 20) { // if the checks written are less than 20, charge 10 cents per check
    charges += (numChecks * 0.1);
  }

  else if (numChecks >= 20 && numChecks <= 39) { // if the checks written are between 29-39, charge
                                                 // 8 cents per check
    charges += (numChecks * 0.08);
  }

  else if (numChecks >= 40 && numChecks <= 59) { // if the checks written are between 39-49, charge
                                                 // 6 cents per check
    charges += (numChecks * 0.06);
  }

  else { // if the checks written are 60 or more, charge 4 cents per check
    charges += (numChecks * 0.04);
  }

  cout << "\n--Bank Charges Statement--\nBeginning balance: $" << fixed << setprecision(2)
       << initialBalance; // sets max decimal places to two
  cout << "\nNumber of checks written: " << numChecks;
  cout << "\nTotal bank Charges: $" << charges;

  return 0;
}
