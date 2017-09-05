#include <iostream>
#include <vector>
using namespace std;

// https://stackoverflow.com/questions/10908012/computing-the-scalar-product-of-two-vectors-in-c

struct VECTOR {
  string name; // vector name
  double x, y; // 2d values of vector
};

void menu(vector<VECTOR>&);
VECTOR get_vector(); // function that creates & returns a vector
VECTOR calc_sum(VECTOR, VECTOR); // adds the values of two VECTOR types
VECTOR print_vector(VECTOR); // function to print contents of vector to file

int main() {
  
  return 0;
}
