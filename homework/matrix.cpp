#include <iostream>
#include <fstream> // file streams
#include <cmath> // abs, sqrt, pow
#include <string>
#include <vector> // vector<TYPE> var
using namespace std;

// template for the abstract data type 'MATRIX'
struct MATRIX {
  string name;
  double data[2][2];
  // 2x2 matrix
  // [a b]
  // [c d]
};

void performOperation(vector<MATRIX>&);
void selectMatrices(const vector<MATRIX>&, MATRIX*, int);
void addMatrices(MATRIX, MATRIX); // adds the values of two VECTOR types
void subMatrices(MATRIX, MATRIX);
void scalarMult(MATRIX);
void scalarProduct(MATRIX, MATRIX);
void inverseMatrix(MATRIX);

void menu();
void printMatrices(const vector<MATRIX>&);
void createMatrix(vector<MATRIX>&);
void deleteMatrix(vector<MATRIX>&);
void menuOption(void (*)(), int&, int); // void (*)() == pointer to void function, ex. menu()
void menuOption(void (*)(const vector<MATRIX>&, MATRIX*, int), int&, int);// overloaded to allow selectMatrices() to be passed as arg
void menuOption(void (*)(vector<MATRIX>& matrices), int&, int); // overloaded to allow performOperation() to be passed as arg
void validateMatrix(MATRIX&, int, int);

void addMatrices(vector<MATRIX>&);

int main() {

  menu(); // fantastic use of a menu *claps*

  return 0;
}


void menu() {
  vector<MATRIX> matrices;
  int menuChoice = -999;

  while(menuChoice != -1) {
    int size = matrices.size();

    cout << "\nEnter -1 to exit the program.\n";

    if(size > 0) {
      cout << "Enter 0 to display matrices.\n";
    }

    cout << "Enter 1 to create a new '2x2' matrix.\n";
    
    if(size > 0) {
      cout << "Enter 2 to delete a matrix.\n";
      cout << "Enter 3 perform an operation on a matrix.\n";
    }

    cout << "\nEnter an option: ";
    menuOption(&menu, menuChoice, 4); // menu() must be passed as a reference!
      
    cout << "\n";

    if(menuChoice == -1) { // exit
      continue;
    }

    else if(menuChoice == 0 && size > 0) // print vectors to console
      printMatrices(matrices);
    
    else if(menuChoice == 1) // create a new 2x2 matrix
      createMatrix(matrices);

    else if(menuChoice == 2 && size > 0) // delete a 2x2 matrix
      deleteMatrix(matrices);
    
    else if(menuChoice == 3 && size > 0) // perform on an operation on a matrix
      performOperation(matrices);
  }
}


void createMatrix(vector<MATRIX>& matrices) {
  MATRIX m;

  cout << "Enter the name for the matrix: "; 
  cin >> m.name;

  for(int x = 0; x < 2; x++) {
    for(int y = 0; y < 2; y++) {
      cout << "Enter the value for row " << x << " column " << y << ": ";
      validateMatrix(m, x ,y);
    }
  }

  matrices.push_back(m);
}


void deleteMatrix(vector<MATRIX>& matrices) {
  int choice;

  cout << "Select a Matrix from the list below that you would like to remove.\n";
  printMatrices(matrices);

  cout << "\nEnter choice: ";
  cin >> choice;

  while(cin.fail() || choice < 0 || choice >= matrices.size()) {
    cin.clear();
		cin.ignore(10000,'\n');
    cout << "Invalid Input! Try again.\n\n";
    deleteMatrix(matrices); // recursive function to loop until correct input is provided
  }

  matrices.erase(matrices.begin()+choice);
}


void printMatrices(const vector<MATRIX>& matrices) {
  for(int i = 0; i < matrices.size(); i++) {
    cout << i << ". " << matrices[i].name << ": ";

    for(int j = 0; j < 2; j++) {
      if(j == 0)
        cout << "\t[ " << matrices[i].data[j][0] << " " << matrices[i].data[j][1] << " ]\n";

      else
        cout << "\t\t[ " << matrices[i].data[j][0] << " " << matrices[i].data[j][1] << " ]\n\n";
    }
  }
}


void menuOption(void (*func)(), int& choice, int size) {
  cin >> choice;

  while(cin.fail() || choice < -1 || choice >= size) {
    cin.clear();
    cin.ignore(10000,'\n');
    cout << "Invalid Input! Try Again.\n";
    (*func)(); // recursively calls the parent function as per input validation
  }
}


void validateMatrix(MATRIX& m, int x, int y) {
  cin >> m.data[x][y];

  while(cin.fail()) {
    cin.clear();
    cin.ignore(10000,'\n');
    cout << "Invalid Input! Try Again.\n";

    cout << "Enter the value for row " << x << " column " << y << ": ";
    cin >> m.data[x][y];
  }
}

/*************************************************
Add Vector Function: Calculates sum of two vectors
Called by: performOperation() function
Calls: none
Parameters: structure vector 1, structure vector 2
Returns: none
*************************************************/
void addMatrices(MATRIX matrix1, MATRIX matrix2) {
  MATRIX m;

  //v.x = (vector1.x + vector2.x);
  //v.y = (vector1.y + vector2.y);

  //cout << "\nSum of vectors " << vector1.name << " and " << vector2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}


/*****************************************************************
Subtract Vector Function: Subtracts one vector from another vector
Parameters: structure vector 1, structure vector 2
Called by: performOperation() function
Calls: none
Returns: none
*****************************************************************/
/*
void subVector(VECTOR vector1, VECTOR vector2) {
  VECTOR v;

  v.x = (vector1.x - vector2.x);
  v.y = (vector1.y - vector2.y);

  cout << "\nSubtraction of vectors " << vector1.name << " and " << vector2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}
*/


/****************************************************************************
Scalar Multiple Function: Multiplies the two values of the vector by a scalar
Parameters: structure vector 1
Called by: performOperation() function
Calls: none
Returns: none
****************************************************************************/
/*
void scalarMult(VECTOR vector1) {
  VECTOR v;
  double choice;

  cout << "\nEnter a scalar value to multiply to vector " << vector1.name << ": ";
  cin >> choice;
  
  v.x = (vector1.x * choice);
  v.y = (vector1.y * choice);

  cout << "\nScalar multiplication of vector " << vector1.name << " times " << choice << " is: ( " << v.x  << ", " << v.y << " )\n";
}
*/


/****************************************************************
Scalar Product Function: Calculates scalar product of two vectors
Parameters: structure vector 1, structure vector 2
Called by: performOperation() function
Calls: none
Returns: none
****************************************************************/
/*
void scalarProduct(VECTOR vector1, VECTOR vector2) {
  VECTOR v;
  
  v.x = (vector1.x * vector2.x);
  v.y = (vector1.y * vector2.y);

  cout << "Scalar product of vectors " << vector1.name << " and " << vector2.name << " is: " << v.x + v.y << "\n";
}
*/


/***********************************************************
 Magnitude Function: Calculates magnitude/length of a vector
 Parameters: structure vector 1
 Called by: performOperation function
 Calls: none
 Returns: none
 **********************************************************/
/*
void magnitude(VECTOR vector1) {
  double magnitude;

  magnitude = abs( sqrt( pow(vector1.x, 2) + pow(vector1.y, 2) ) );

  cout << "\nThe magnitude of vector " << vector1.name << " is: " << magnitude << "\n";
}
*/


void performOperation(vector<MATRIX>& matrices) {
  MATRIX m[2];
  int menuChoice;

  selectMatrices(matrices, m, -999); // selects the first matrix to perform the operation

  cout << "\nSelect the operation you would like to perform on vector '" << m[0].name << "'\n";
  cout << "Enter 1 to add another matrix to '" << m[0].name << "'\n";
  cout << "Enter 2 to subtract matrix '" << m[0].name << "' by another matrix\n";
  cout << "Enter 3 to multiply matrix '" << m[0].name << "' by a scalar.\n";
  cout << "Enter 4 to multiply matrix '" << m[0].name << "' by another matrix\n";
  cout << "Enter 5 to get the inverse of matrix '" << m[0].name << "'\n";

  menuOption(&performOperation, menuChoice, 6); // gets and validates the input

  selectMatrices(matrices, m, menuChoice); // 
}


void selectMatrices(const vector<MATRIX>& matrices, MATRIX m[2], int operation) {
  int menuChoice;
  int size = matrices.size();
  string matrixName = m[0].name;

  if(operation == -999) {
    cout << "Select a matrix from the list below to perform an operation on.\n";
    printMatrices(matrices);
    menuOption(&selectMatrices, menuChoice, size);
    m[0] = matrices[menuChoice];
  }

  else if(operation == 1) {
    cout << "Select a matrix from the list to add to '" << matrixName << "': ";
    printMatrices(matrices);
    menuOption(&selectMatrices, menuChoice, size);
    m[1] = matrices[menuChoice];
  }

  else if(operation == 2) {
    cout << "Select a matrix from the list to subtract from matrix '" << matrixName << "': ";
    printMatrices(matrices);
    menuOption(&selectMatrices, menuChoice, size);
    m[1] = matrices[menuChoice];
  }

  else if(operation == 4) {
    cout << "Select a matrix from the list to multiply to matrix '" << matrixName << "': ";
    printMatrices(matrices);
    menuOption(&selectMatrices, menuChoice, size);
    m[1] = matrices[menuChoice];
  }

  else if(operation == 5) {
    printMatrices(matrices);
    menuOption(&selectMatrices, menuChoice, size);
    // inverseMatrix()
    //m[1] = matrices[menuChoice];
  }
}
