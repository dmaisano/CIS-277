#include <iostream>
#include <regex>
#include <string>
using namespace std;

// return an array of the total cost, and the cost of the previous line
int *getCost(int currentCost, int costs[]) {
  // total cost
  costs[0] += currentCost * currentCost * currentCost;

  // previous cost
  costs[1] = currentCost;

  return costs;
}

void neat(int maxLength) {
  string result = "";
  int lineLength = 0; // length of the current line
  int costs[] = {0, 0};

  string word;
  while (cin >> word) {

    if (lineLength + word.length() > maxLength) {
      int numSpaces = maxLength - lineLength;
      result += ' ' * numSpaces;
    }

    // check if word fits line
    if (lineLength < maxLength) {
      result += word;
      lineLength += word.length();

      // add space if fits
      if (lineLength < maxLength) {
        result += ' ';
        lineLength += 1;
      }
    }

    // add newline
    if (lineLength == maxLength) {
      lineLength = 0;
      result += '\n';
    }
  }

  cout << result << endl;
}

int main(int argc, char *argv[]) {
  int lineLength = 60;

  // check if arg is int
  if (argv[1] && regex_match(argv[1], regex("[0-9]+"))) {
    lineLength = stoi(argv[1]);
  }

  neat(lineLength);

  // int costs[] = {0, 0};

  // getCost(2, costs);

  // cout << costs[0] << endl;
  // cout << costs[1] << endl;
}
