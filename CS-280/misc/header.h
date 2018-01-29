#ifndef NUM_H
#define NUM_H
using namespace std;

class Dog {
private:
  string name, breed;
  int age;

public:
  Dog() {
    cout << "Enter the name for the dog: ";
    cin >> name;

    cout << "How old is " << this->name << ": ";
    cin >> age;

    cout << "What breed is " << this->name << ": ";
    cin >> breed;

    this->name = name;
    this->age = age;
    this->breed = breed;
  }

  string getName() {
    return this->name;
  }

  int getAge() {
    return this->age;
  }

  string getBreed() {
    return this->breed;
  }
};

#endif 
