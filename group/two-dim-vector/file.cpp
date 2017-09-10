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

void getVectors(vector<VECTOR>&);
void deleteVector(vector<VECTOR>&);
void splitVector(vector<VECTOR>&, string);
void createVector(vector<VECTOR>&);
void writeVector(const vector<VECTOR>&);
void printVector(const vector<VECTOR>&);

int main() {
  vector<VECTOR> vect;
  getVectors(vect);

  deleteVector(vect);
  
  return 0;
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
