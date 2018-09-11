#include <iostream>
#include <string>
#include <vector>
using namespace std;

// returns 0 if no list provided
auto reduce = [](vector<int> nums = {0}) {
  int sum = 0;

  for (auto num : nums)
    sum += num;

  return sum;
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};

  cout << reduce(nums);
}
