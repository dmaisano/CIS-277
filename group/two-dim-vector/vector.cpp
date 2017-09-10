#include <iostream>
#include <fstream> // file streams
#include <string>
#include <sstream> // stringstream
#include <vector> // vector<TYPE> var
using namespace std;

struct VECTOR {
  string name; // vector name
  double x, y; // 2d values of vector
};

void performOperation(vector<VECTOR>);
VECTOR selectSecondVector(const vector<VECTOR>, VECTOR, string); // select second vector that will be performed in the operation
void addVector(VECTOR, VECTOR); // adds the values of two VECTOR types
void subVector(VECTOR, VECTOR);
void scalarMult(VECTOR);
void scalarProduct(VECTOR, VECTOR);
void magnitude(VECTOR);

void getVectors(vector<VECTOR>&);
void deleteVector(vector<VECTOR>&);
void splitVector(vector<VECTOR>&, string);
void createVector(vector<VECTOR>&);
void writeVector(const vector<VECTOR>&);
void printVector(const vector<VECTOR>&);

void menu();

int main() {
  menu(); // best main function 10/10
  // so clean, much wow, very amaze
  
  return 0;
}

void menu() {
  int menuChoice = -99;
  
  while(menuChoice != -1) {
    vector<VECTOR> vect;
    getVectors(vect);
    int size = vect.size();

    cout << "\nEnter -1 to exit the program.\n";

    if(size > 0) {
      cout << "Enter 0 to display vectors.\n";
    }

    cout << "Enter 1 to create a new vector.\n";
    
    if(size > 0) {
      cout << "Enter 2 to delete a vector.\n";
      cout << "Enter 3 perform an operation on a vector.\n";
    }

    cout << "\nEnter an option: ";
    cin >> menuChoice;

    cout << "\n";

    if(menuChoice == -1) { // exit
      writeVector(vect);
      continue;
    }

    else if(menuChoice == 0 && size > 0) // print vectors to console
      printVector(vect);
    
    else if(menuChoice == 1)
      createVector(vect);

    else if(menuChoice == 2 && size > 0)
      deleteVector(vect);
    
    else if(menuChoice == 3 && size > 0)
      performOperation(vect);

  }
}

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


void getVectors(vector<VECTOR>& vect) {
  string currentLine;
  ifstream dataFile("vector.dat");

  while(getline(dataFile, currentLine)) {
    splitVector(vect, currentLine);
  }

  dataFile.close(); // close file when done
}

void deleteVector(vector<VECTOR>& vect) {
  int choice;

  cout << "Select a vector from the list below that you would like to remove.\n";
  printVector(vect);

  cout << "\nEnter choice: ";
  cin >> choice;

  vect.erase(vect.begin()+choice);
  writeVector(vect);
}

void createVector(vector<VECTOR>& vect) {
  VECTOR v;

  cout << "Enter the name for the vector: "; // assign the name to the vector
  cin >> v.name;

  cout << "Enter the first value of the vector: "; // assign first number to the vector
  cin >> v.x;

  cout << "Enter the second value of the vector: "; // assign second number to the vector;
  cin >> v.y;

  vect.push_back(v);
  writeVector(vect); // saves the vector to the file after creation
}

void splitVector(vector<VECTOR>& vect, string line) {
  VECTOR v;
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
      vect.push_back(v);
    }
  }
}

void writeVector(const vector<VECTOR>& vect) {
  ofstream textFile("vector.txt", ios::out | ios::trunc); // clears the content of the file to prevent duplication
  ofstream dataFile("vector.dat", ios::out | ios::trunc);

  for(int i = 0; i < vect.size(); i++) {
    dataFile << vect[i].name << "," << vect[i].x << "," << vect[i].y;
    textFile << "Vector Name: " << vect[i].name << " ( " << vect[i].x << ", " << vect[i].y << " )";

    if(i != (vect.size() - 1)) { // prevents empty lines from being added to file
      textFile << "\n";
      dataFile << "\n";
    }
  }

  dataFile.close(); // close file when done
}

void printVector(const vector<VECTOR>& vect) {
  for(int i = 0; i < vect.size(); i++) {
    cout << i << ". " << vect[i].name << ": ( " << vect[i].x << ", " << vect[i].y << " )\n";
  }
}
