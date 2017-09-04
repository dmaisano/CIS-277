#include <iostream>
using namespace std;

struct VECTOR {
  string name; // vector name
  double x, y; // 2d values of vector
};

VECTOR get_vector(); // function that creates & returns a vector
VECTOR calc_sum(VECTOR, VECTOR); // adds the values of two VECTOR types
VECTOR print_vector(VECTOR); // function to print contents of vector to file

int main() {
  //VECTOR nums = {1, 3}; // vector type declaration
  //int size = sizeof(nums) / sizeof(nums.x); // Returns size of the Vector Struct

  VECTOR vect1 = get_vector(); // create vector1
  VECTOR vect2 = get_vector(); // create vector2

  /*
  cout << vect1.name << " =  ( " << vect1.x << ", " << vect1.y << " )";

  cout << vect2.name << " =  ( " << vect2.x << ", " << vect2.y << " )";
  */

  VECTOR sum = calc_sum(vect1, vect2);

  cout << sum.name << " =  ( " << sum.x << ", " << sum.y << " )";
  
  return 0;
}

VECTOR get_vector() {
  VECTOR v;

  cout << "Enter the name for the vector: "; // assign the name to the vector
  cin >> v.name;

  cout << "Enter the first value of the vector: "; // assign first number to the vector
  cin >> v.x;

  cout << "Enter the second value of the vector: "; // assign second number to the vector;
  cin >> v.y;

  return v;
}

VECTOR calc_sum(VECTOR vector1, VECTOR vector2) {
  VECTOR v;

  cout << "Enter the new name for the sum of the vectors: ";
  cin >> v.name;

  v.x = (vector1.x + vector2.x);

  v.y = (vector2.y + vector2.y);

  return v;
}

VECTOR print_vector(VECTOR vector) {
  // code goes here
}
