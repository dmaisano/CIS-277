/*
CIS-277-601HY
Domenico Maisano
Prof. Aljamal
Matrix Project
*/

#include <iostream>
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

// Operations Functions
void performOperation(vector<MATRIX>&); // performs an operation on a MATRIX
void selectMatrices(const vector<MATRIX>&, MATRIX*, int); // selects one or more MATRICES to be used for the operation(s)
void addMatrices(MATRIX, MATRIX); // adds the values of two MATRICES
void subMatrices(MATRIX, MATRIX); // subtracts the values of two MATRICES
void scalarProduct(MATRIX, MATRIX); // multiplies the values of a MATRIX by a scalar value 
void scalarMult(MATRIX); // multiplies the values of two MATRICES
void inverseMatrix(MATRIX, vector<MATRIX>&); // operation to get the inverse of a MATRIX

// General Menu Functions
void menu(vector<MATRIX>& matrices); // main menu for user interaction
void printMatrix(const MATRIX); // prints a single MATRIX
void printMatrices(const vector<MATRIX>&); // prints all the MATRICESfrom the vector<MATRIX>
void createMatrix(vector<MATRIX>&); // creates a MATRIX to the vector<MATRIX>
void deleteMatrix(vector<MATRIX>&); // deletes a MATRIX from the vector<MATRIX>

// Input Validation Functions
bool validateMenu(int&, int); // used for recursive input validation for a menu/sub-menu
void validateMatrix(MATRIX&, int, int = 1); // validates the input for each MATRIX row & col
void validateScalar(void (*)(MATRIX, MATRIX), double&); // validates the input for scalarMult()


int main() {
  vector<MATRIX> matrices;

  menu(matrices);

  return 0;
}


void menu(vector<MATRIX>& matrices) {
  int userInput = -999;
  bool menuReturn;
  // 0 = error raised
  // 1 = no error

  while(userInput != -1) {
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
    menuReturn = validateMenu(userInput, 4); // menu() must be passed as a reference!
    if(menuReturn == false) {
      menu(matrices);
    }

    cout << "\n";

    if(userInput == -1) // exit
      break;

    else if(userInput == 0 && size > 0) // print vectors to console
      printMatrices(matrices);
    
    else if(userInput == 1) // create a new 2x2 matrix
      createMatrix(matrices);

    else if(userInput == 2 && size > 0) // delete a 2x2 matrix
      deleteMatrix(matrices);
    
    else if(userInput == 3 && size > 0) // perform on an operation on a matrix
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
    cout << i << ". " << matrices[i].name << ":\n";

    for(int j = 0; j < 2; j++) {
      if(j == 0)
        cout << "[ " << matrices[i].data[j][0] << " " << matrices[i].data[j][1] << " ]\n";

      else
        cout << "[ " << matrices[i].data[j][0] << " " << matrices[i].data[j][1] << " ]\n\n";
    }
  }
}


void printMatrix(const MATRIX matrix) {
  for(int j = 0; j < 2; j++) {
    if(j == 0)
      cout << "\n[ " << matrix.data[j][0] << " " << matrix.data[j][1] << " ]\n";

    else
      cout << "[ " << matrix.data[j][0] << " " << matrix.data[j][1] << " ]\n\n";
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


void addMatrices(MATRIX matrix1, MATRIX matrix2) {
  MATRIX m;

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      m.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
    }
  }

  cout << "\nSum of matrices " << matrix1.name << " and " << matrix2.name << " is: ";
  printMatrix(m);
}


void subMatrices(MATRIX matrix1, MATRIX matrix2) {
  MATRIX m;
  
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      m.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
    }
  }

  cout << "\nSubtraction of matrices " << matrix1.name << " and " << matrix2.name << " is: ";
  printMatrix(m);
}


/****************************************************************************
Scalar Multiple Function: Multiplies the Matrix by a scalar value
Parameters: structure vector 1
Called by: performOperation() function
Calls: none
Returns: none
****************************************************************************/
void scalarMult(MATRIX matrix1) {
  MATRIX m;
  double scalar;

  cout << "Enter a Scalar value to multiple to matrix '" << m.name << "': ";
  cin >> scalar;

  while(cin.fail()) {
    cin.clear();
		cin.ignore(10000,'\n');
    cout << "Invalid Input! Try again.\n\n";
    cout << "Enter a Scalar value to multiple to matrix '" << m.name << "': ";
    cin >> scalar;
  }
  
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      m.data[i][j] = scalar * matrix1.data[i][j];
    }
  }

  cout << "\nScalar multiple of matrix '" << matrix1.name << "' and scalar '" << scalar<< "' is: ";
  printMatrix(m);
}



void scalarProduct(MATRIX matrix1, MATRIX matrix2) {
  MATRIX m;
  
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      m.data[i][j] = matrix1.data[i][j] * matrix2.data[i][j];
    }
  }

  cout << "\nProduct of matrices " << matrix1.name << " and " << matrix2.name << " is: ";
  printMatrix(m);
}


void inverseMatrix(MATRIX matrix1, vector<MATRIX>& matrices) {
  MATRIX inverse, swappedMatrix;
  double determinant;
  double a, b, c, d;

  a = matrix1.data[0][0];
  b = matrix1.data[0][1];
  c = matrix1.data[1][0];
  d = matrix1.data[1][1];

  swappedMatrix.data[0][0] = d;
  swappedMatrix.data[0][1] = b * -1;
  swappedMatrix.data[1][0] = c * -1;
  swappedMatrix.data[1][1] = a;

  if((a*d) - (b*c) == 0) { // avoid divide by zero error
    cout << "Invalid matrix! 'ad - bc' equals zero.\nCannot divide by Zero! Select another matrix!\n";
    menu(matrices); // goes back to menu for user to select other options
  }
  
  else {
    determinant = 1 / (a*d) - (b*c);
  
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 2; j++) {
        inverse.data[i][j] = determinant * swappedMatrix.data[i][j];
      }
    }

    cout << "\nThe inverse of matrix '" << matrix1.name << "' is: ";
    printMatrix(inverse);
  }
}


void performOperation(vector<MATRIX>& matrices) {
  MATRIX m[2];
  bool menuReturn;
  int userInput;

  selectMatrices(matrices, m, -999); // selects the first matrix to perform the operation

  cout << "\nSelect the operation you would like to perform on Matrix '" << m[0].name << "'\n";
  if(matrices.size() > 0) {
    cout << "Enter 1 to add another matrix to '" << m[0].name << "'\n";
    cout << "Enter 2 to subtract another matrix to matrix '" << m[0].name << "' by another matrix\n";
    cout << "Enter 3 to multiply matrix '" << m[0].name << "' by another matrix\n";
    cout << "Enter 4 to multiply matrix '" << m[0].name << "' by a scalar.\n";
  }
  cout << "Enter 5 to get the inverse of matrix '" << m[0].name << "'\n";
  cout << "\nEnter an option: ";

  menuReturn = validateMenu(userInput, 6); // gets and validates the input (6 is the max menu size)
  if(menuReturn == false) { // if false, error was raised, recursively call menu
    performOperation(matrices);
  }

  selectMatrices(matrices, m, userInput); // 
}


void selectMatrices(const vector<MATRIX>& matrices, MATRIX m[2], int operation) {
  int userInput;
  int size = matrices.size();
  string matrixName = m[0].name;
  bool menuReturn;
  vector<MATRIX> temp = matrices;

  if(operation == -999) {
    cout << "Select a matrix from the list below to perform an operation on.\n";
    printMatrices(matrices);
    cout << "Enter an option: ";
    menuReturn = validateMenu(userInput, size);
    if(menuReturn == false) {
      performOperation(temp);
    }
    m[0] = matrices[userInput];
  }

  else if(operation == 1) {
    cout << "Select a matrix from the list to add to '" << matrixName << "'\n";
    printMatrices(matrices);
    cout << "Enter an option: ";
    menuReturn = validateMenu(userInput, size);
    if(menuReturn == false) {
      performOperation(temp);
    }
    m[1] = matrices[userInput];
    addMatrices(m[0], m[1]);
  }

  else if(operation == 2) {
    cout << "Select a matrix from the list to subtract from matrix '" << matrixName << "'\n";
    printMatrices(matrices);
    cout << "Enter an option: ";
    menuReturn = validateMenu(userInput, size);
    if(menuReturn == false) {
      performOperation(temp);
    }
    m[1] = matrices[userInput];
    subMatrices(m[0], m[1]);
  }

  else if(operation == 3) {
    cout << "Select a matrix from the list to multiply to matrix '" << matrixName << "''\n";
    printMatrices(matrices);
    cout << "Enter an option: ";
    menuReturn = validateMenu(userInput, size);
    if(menuReturn == false) {
      performOperation(temp);
    }
    m[1] = matrices[userInput];
    scalarProduct(m[0], m[1]);
  }

  else if(operation == 4) {
    cout << "Select a matrix from the list to multiply by a scalar''\n";
    printMatrices(matrices);
    cout << "Enter an option: ";
    menuReturn = validateMenu(userInput, size);
    if(menuReturn == false) {
      performOperation(temp);
    }
    m[1] = matrices[userInput];
    scalarMult(m[1]);
  }

  else if(operation == 5) {
    inverseMatrix(m[0], temp);
  }
}


bool validateMenu(int& choice, int size) {
  cin >> choice;

  if(cin.fail() || choice < -1 || choice >= size) {
    cin.clear();
    cin.ignore(10000,'\n');
    cout << "Invalid Input! Try Again.\n";
    return false;
  }

  else {
    return true;
  }
}
