#include <iostream>
#include <vector> // vector
#include "struct.hpp"
#include "file.hpp"
using namespace std;

void performOperation(vector<VECTOR>);
VECTOR selectSecondVector(const vector<VECTOR>, VECTOR, string); // select second vector that will be performed in the operation
void addVector(VECTOR, VECTOR); // adds the values of two VECTOR types
void subVector(VECTOR, VECTOR);
void scalarMult(VECTOR);
void scalarProduct(VECTOR, VECTOR);
void magnitude(VECTOR);

void addVector(VECTOR vector1, VECTOR vector2) {
  VECTOR v;

  v.x = (vector1.x + vector2.x);
  v.y = (vector1.y + vector2.y);

  cout << "\nSum of vectors " << vector1.name << " and " << vector2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}

void subVector(VECTOR vector1, VECTOR vector2) {
  VECTOR v;

  v.x = (vector1.x - vector2.x);
  v.y = (vector1.y - vector2.y);

  cout << "\nSubtraction of vectors " << vector1.name << " and " << vector2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}

void scalarMult(VECTOR vector1) {
  VECTOR v;
  double choice;

  cout << "\nEnter a scalar value to multiply to vector " << vector1.name << ": ";
  cin >> choice;
  
  v.x = (vector1.x * choice);
  v.y = (vector1.y * choice);

  cout << "\nScalar multiplication of vector " << vector1.name << " times " << choice << " is: ( " << v.x  << ", " << v.y << " )\n";
}

void scalarProduct(VECTOR vector1, VECTOR vector2) {
  VECTOR v;
  
  v.x = (vector1.x * vector2.x);
  v.y = (vector1.y * vector2.y);

  cout << "\nMultiplication of vectors " << vector1.name << " and " << vector2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}

void magnitude(VECTOR vector1) {
  double magnitude;

  magnitude = (vector1.x * vector1.x) + (vector1.y * vector1.y);

  cout << "\nThe magnitude of vector " << vector1.name << " is: " << magnitude << "\n";
}

void performOperation(vector<VECTOR> vect) {
  VECTOR vector1, vector2;
  int choice[2];
  
  cout << "Select a vector from the list below to perform an operation on.\n";
  printVector(vect);

  cout << "\nEnter choice: ";
  cin >> choice[0];

  vector1 = vect[choice[0]];

  cout << "\nSelect the operation you would like to perform on vector '" << vector1.name << "'\n";
  cout << "Enter 1 to add another vector to '" << vector1.name << "'\n";
  cout << "Enter 2 to subtract vector '" << vector1.name << "' by another vector\n";
  cout << "Enter 3 to multiply vector '" << vector1.name << "' by a scalar.\n";
  cout << "Enter 4 to multiply vector '" << vector1.name << "' by another vector\n";
  cout << "Enter 5 to get the magnitude of vector '" << vector1.name << "'\n";

  cout << "\nEnter choice: ";
  cin >> choice[1];

  if(choice[1] == 1) {
    vector2 = selectSecondVector(vect, vector1, "add");
    addVector(vector1,vector2);
  }

  else if(choice[1] == 2) {
    vector2 = selectSecondVector(vect, vector1, "subtract");
    subVector(vector1,vector2);
  }

  else if(choice[1] == 3) {
    scalarMult(vector1);
  }
  
  else if(choice[1] == 4) {
    vector2 = selectSecondVector(vect, vector1, "multiply");
    scalarProduct(vector1,vector2);
  }

  else if(choice[1] == 5) {
    magnitude(vector1);
  }

  else {
    cout << "Invalid choice.\n";
    performOperation(vect);
  }
}

VECTOR selectSecondVector(const vector<VECTOR> vect, VECTOR vector1, string operation) {
  VECTOR vector2;
  int choice;

  cout << "\nSelect from the list below the second vector to " << operation << " to vector " << vector1.name << ".\n";
  printVector(vect);

  cout << "\nEnter choice: ";
  cin >> choice;
  vector2 = vect[choice];

  return vector2;
}
