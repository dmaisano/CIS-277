#include <iostream>
#include <fstream> // file streams
#include <cmath> // abs, sqrt, pow
#include <string>
#include <sstream> // stringstream
#include <vector> // vector<TYPE> var
using namespace std;

// template for the abstract data type 'MATRIX'
struct MATRIX {
  string name;
  double a11, a12, a21, a22; 
  // 2x2 matrix
  // [a b]
  // [c d]
};

void performOperation(vector<MATRIX>);
MATRIX selectSecondMatrix(const vector<MATRIX>, MATRIX, string); // select second vector that will be performed in the operation
void addMatrix(MATRIX, MATRIX); // adds the values of two MATRIX types
void subMatrix(MATRIX, MATRIX);
void scalarMult(MATRIX);
void scalarProduct(MATRIX, MATRIX);
void magnitude(MATRIX);

void getMatrix(vector<MATRIX>&);
void deleteMatrix(vector<MATRIX>&);
void splitMatrix(vector<MATRIX>&, string);
void createMatrix(vector<MATRIX>&);
void writeMatrix(const vector<MATRIX>&);
void printMatrix(const vector<MATRIX>&);

double validateDouble(string);


int main() {
  menu();
  
  return 0;
}


/*********************************************************
Menu Function: provides user with menu to create, display,
delete, or perform operations on Matrices
Parameters: none
Called by: main function
Calls: get matrix, write matrix, print matrix,
create vector, delete vector, perform operations
Returns: none
**********************************************************/
void menu() {
  int menuChoice = -99;
  
  while(menuChoice != -1) {
    vector<MATRIX> matrix;
    getMatrix(matrix);
    int size = matrix.size();

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
    cin >> menuChoice;

    while(cin.fail() || menuChoice < -1 || menuChoice > 3) {
      cin.clear();
      cin.ignore(10000,'\n');
      cout << "Invalid Input! Try Again.\n";
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
      cin >> menuChoice;
    }
      
    cout << "\n";

    if(menuChoice == -1) { // exit
      writeVector(matrix);
      continue;
    }

    else if(menuChoice == 0 && size > 0) // print vectors to console
      printVector(matrix);
    
    else if(menuChoice == 1)
      createMatrix(matrix);

    else if(menuChoice == 2 && size > 0)
      deleteVector(matrix);
    
    else if(menuChoice == 3 && size > 0)
      performOperation(matrix);

  }
}


/*************************************************
Add Matrix Function: Calculates sum of two vectors
Called by: performOperation() function
Calls: none
Parameters: structure matrix 1, structure matrix 2
Returns: none
*************************************************/
void addVector(MATRIX matrix1, MATRIX matrix2) {
  MATRIX m;

  //v.x = (matrix1.x + matrix2.x);
  //v.y = (matrix1.y + matrix2.y);

  //cout << "\nSum of vectors " << matrix1.name << " and " << matrix2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}


/*****************************************************************
Subtract Vector Function: Subtracts one vector from another vector
Parameters: structure vector 1, structure vector 2
Called by: performOperation() function
Calls: none
Returns: none
*****************************************************************/
void subVector(MATRIX matrix1, MATRIX matrix2) {
  MATRIX v;

  //v.x = (matrix1.x - matrix2.x);
  //v.y = (matrix1.y - matrix2.y);

  //cout << "\nSubtraction of vectors " << matrix1.name << " and " << matrix2.name << " is: ( " << v.x  << ", " << v.y << " )\n";
}


/****************************************************************************
Scalar Multiple Function: Multiplies the two values of the vector by a scalar
Parameters: structure vector 1
Called by: performOperation() function
Calls: none
Returns: none
****************************************************************************/
void scalarMult(MATRIX matrix1) {
  MATRIX v;
  double choice;

  cout << "\nEnter a scalar value to multiply to vector " << matrix1.name << ": ";
  cin >> choice;
  
  v.x = (matrix1.x * choice);
  v.y = (matrix1.y * choice);

  cout << "\nScalar multiplication of vector " << matrix1.name << " times " << choice << " is: ( " << v.x  << ", " << v.y << " )\n";
}


/****************************************************************
Scalar Product Function: Calculates scalar product of two vectors
Parameters: structure vector 1, structure vector 2
Called by: performOperation() function
Calls: none
Returns: none
****************************************************************/
void scalarProduct(MATRIX matrix1, MATRIX matrix2) {
  MATRIX v;
  
  v.x = (matrix1.x * matrix2.x);
  v.y = (matrix1.y * matrix2.y);

  cout << "Scalar product of vectors " << matrix1.name << " and " << matrix2.name << " is: " << v.x + v.y << "\n";
}


/***********************************************************
 Magnitude Function: Calculates magnitude/length of a vector
 Parameters: structure vector 1
 Called by: performOperation function
 Calls: none
 Returns: none
 **********************************************************/
/*
void magnitude(MATRIX m) {
  double magnitude;

  magnitude = abs( sqrt( pow(m.x, 2) + pow(matrix1.y, 2) ) );

  cout << "\nThe magnitude of vector " << matrix1.name << " is: " << magnitude << "\n";
}
*/


/******************************************************************************************************************
 Perform Operation Function: Sub-Menu function that allows user to choose desired operation to perform on vector(s)
 Parameters: vector data type
 Called by: menu() function
 Calls: print vector function, select second vector function, add vector function, subtract vector function, 
 scalar multiple function, scalar product function, magnitude function, perform operation function
 Returns: none
 *****************************************************************************************************************/
void performOperation(vector<MATRIX> matrix) {
  MATRIX matrix1, matrix2;
  int choice[2];
  
  cout << "Select a vector from the list below to perform an operation on.\n";
  printVector(matrix);

  cout << "\nEnter choice: ";
  cin >> choice[0];

  while(cin.fail() || choice[0] < 0 || choice[0] > matrix.size()) { // input validation for selecting the second vector
    cin.clear();
		cin.ignore(10000,'\n');
    cout << "Invalid Input! Try again.\n\n";

    cout << "Select a vector from the list below to perform an operation on.\n";
    printVector(matrix);
  
    cout << "\nEnter choice: ";
    cin >> choice[0];
  }

  matrix1 = matrix[choice[0]]; // creates the first MATRIX based on the user's input

  cout << "\nSelect the operation you would like to perform on vector '" << matrix1.name << "'\n";
  cout << "Enter 1 to add another vector to '" << matrix1.name << "'\n";
  cout << "Enter 2 to subtract vector '" << matrix1.name << "' by another vector\n";
  cout << "Enter 3 to multiply vector '" << matrix1.name << "' by a scalar.\n";
  cout << "Enter 4 to multiply vector '" << matrix1.name << "' by another vector\n";
  cout << "Enter 5 to get the magnitude of vector '" << matrix1.name << "'\n";

  cout << "\nEnter choice: ";
  cin >> choice[1];

  while(cin.fail() || choice[1] < 1 || choice[1] > 5) {
    cin.clear();
		cin.ignore(10000,'\n');
    cout << "Invalid Input! Try again.\n\n";

    cout << "\nSelect the operation you would like to perform on vector '" << matrix1.name << "'\n";
    cout << "Enter 1 to add another vector to '" << matrix1.name << "'\n";
    cout << "Enter 2 to subtract vector '" << matrix1.name << "' by another vector\n";
    cout << "Enter 3 to multiply vector '" << matrix1.name << "' by a scalar.\n";
    cout << "Enter 4 to multiply vector '" << matrix1.name << "' by another vector\n";
    cout << "Enter 5 to get the magnitude of vector '" << matrix1.name << "'\n";
  }


  if(choice[1] == 1) {
    matrix2 = selectSecondVector(matrix, matrix1, "add"); // selects a second vector
    addVector(matrix1,matrix2);
  }

  else if(choice[1] == 2) {
    matrix2 = selectSecondVector(matrix, matrix1, "subtract"); // selects a second vector
    subVector(matrix1,matrix2);
  }

  else if(choice[1] == 3) {
    scalarMult(matrix1);
  }
  
  else if(choice[1] == 4) {
    matrix2 = selectSecondVector(matrix, matrix1, "multiply"); // selects a second vector
    scalarProduct(matrix1,matrix2);
  }

  else if(choice[1] == 5) {
    magnitude(matrix1);
  }

  else {
    cout << "Invalid Input! Try again.\n";
    performOperation(matrix);
  }
}


/*************************************************************************
Select Second Vector Function: selects second vector to perform operations
Parameters: constant vector data type, structure vector 1, string
Called by: perform operation function
Calls: print vector function
Returns: vector
*************************************************************************/
MATRIX selectSecondVector(const vector<MATRIX> matrix, MATRIX matrix1, string operation) {
  MATRIX matrix2;
  int choice;

  cout << "\nSelect from the list below the second vector to " << operation << " to vector " << matrix1.name << ".\n";
  printVector(matrix);

  cout << "\nEnter choice: ";
  cin >> choice;

  while(cin.fail() || choice < 0 || choice > matrix.size()) {
    cin.clear();
		cin.ignore(10000,'\n');
    cout << "Invalid Input! Try again.\n\n";

    cout << "Select from the list below the second vector to " << operation << " to vector " << matrix1.name << ".\n";
    printVector(matrix);
  
    cout << "\nEnter choice: ";
    cin >> choice;
  }

  matrix2 = matrix[choice];

  return matrix2;
}


void getMatrix(vector<MATRIX>& matrix) {
  string currentLine;
  ifstream dataFile("matrix.dat");

  while(getline(dataFile, currentLine)) {
    splitVector(matrix, currentLine);
  }

  dataFile.close(); // close file when done
}

void deleteVector(vector<MATRIX>& matrix) {
  int choice;

  cout << "Select a vector from the list below that you would like to remove.\n";
  printVector(matrix);

  cout << "\nEnter choice: ";
  cin >> choice;

  while(cin.fail() || choice < 0 || choice > matrix.size()) {
    cin.clear();
		cin.ignore(10000,'\n');
    cout << "Invalid Input! Try again.\n\n";

    cout << "Select a vector from the list below that you would like to remove.\n";
    printVector(matrix);
  
    cout << "\nEnter choice: ";
    cin >> choice;
  }

  matrix.erase(matrix.begin()+choice);
  writeVector(matrix);
}


/*********************************************************************
Create Vector Function: Creates a MATRIX data type based on user input
Parameters: vector data type
Called by: menu function
Calls: writeMatrix() function, validateDouble() function
Returns: none
**********************************************************************/
void createMatrix(vector<MATRIX>& matrix) {
  MATRIX m;

  cout << "Enter the name for the matrix: "; // assign the name to the vector
  cin >> m.name;

  cout << "Enter the top-left value of the vector: "; // assign first number to the vector
  m.a11 = validateDouble("Enter the top-left value of the vector: ");

  cout << "Enter the top-right value of the vector: "; // assign first number to the vector
  m.a12 = validateDouble("Enter the top-right value of the vector: ");

  cout << "Enter the bottom-left value of the vector: "; // assign first number to the vector
  m.a21 = validateDouble("Enter the bottom-left value of the vector: ");

  cout << "Enter the bottom-right value of the vector: "; // assign first number to the vector
  m.a22 = validateDouble("Enter the bottom-right value of the vector: ");

  matrix.push_back(m);
  writeVector(matrix); // saves the vector to the file after creation
}


/**************************************************************************************
Split Vector Function: Splits the current line of the data file into readable string(s)
Parameters: vector data type, string
Called by: getVectors() function
Calls: none
Returns: none
**************************************************************************************/
void splitVector(vector<MATRIX>& matrix, string line) {
  MATRIX v;
  istringstream ss(line);

  for(int i = 0; i < 3; i++) {
    string item;
    getline(ss, item, ',');

    if(item == "") // ignores a line if empty
      continue;

    if(i == 0)
      v.name = item;

    else if(i == 1)
      istringstream(item) >> v.x;
      
    else if(i == 2) {
      istringstream(item) >> v.y;
      matrix.push_back(v);
    }
  }
}


/***********************************************************************
Write Vector Function: Writes the existing vector data to file(s)
Parameters: constant MATRIX data type
Called by: createVector() function, deleteVector() function, menu() function
Calls: none
Returns: none
***********************************************************************/
void writeVector(const vector<MATRIX>& matrix) {
  ofstream textFile("vector.txt", ios::out | ios::trunc); // clears the content of the file to prevent duplication
  ofstream dataFile("vector.dat", ios::out | ios::trunc);

  for(int i = 0; i < matrix.size(); i++) {
    dataFile << matrix[i].name << "," << matrix[i].x << "," << matrix[i].y;
    textFile << "Vector Name: " << matrix[i].name << " ( " << matrix[i].x << ", " << matrix[i].y << " )";

    if(i != (matrix.size() - 1)) { // prevents empty lines from being added to file
      textFile << "\n";
      dataFile << "\n";
    }
  }

  dataFile.close(); // close file when done
}


/****************************************************************
Print File Function: Prints vector data to console
Parameters: constant vector data type
Called by: deleteVector() function, selectSecondVector() function,
perform operation function, menu function
Calls: none
Returns: none
****************************************************************/
void printVector(const vector<MATRIX>& matrix) {
  for(int i = 0; i < matrix.size(); i++) {
    cout << i << ". " << matrix[i].name << ": ( " << matrix[i].x << ", " << matrix[i].y << " )\n";
  }
}


/***************************************************************************************
Vadlidate Double Function: Input validation for user input that must be of type 'double'
This includes error checking so the user can't type a invalid number
Parameters: string that contains the phrase to display to the user
Called by: createVector()
Calls: none
Returns: Valid number from user
***************************************************************************************/
double validateDouble(string phrase) {
  double input;
  cin >> input;

  while(cin.fail()) {
    cin.clear();
    cin.ignore(10000,'\n');
    cout << "Invalid Input! Try Again.\n";

    cout << phrase;
    cout << "\nEnter an option: ";
    cin >> input;
  }

  return input;
}
