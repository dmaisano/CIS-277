#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
using namespace std;

class Foo
{
private:
	static void doSomething()
	{
		cout << "foo bar baz";
	}

public:
	static void bar();
};

void Foo::bar()
{
	doSomething();
}

class Dog
{
private:
	string name, breed;
	int age;

public:
	Dog()
	{
		cout << "Enter the name for the dog: ";
		cin >> this->name;

		cout << "How old is " << this->name << ": ";
		cin >> this->age;

		cout << "What breed is " << this->name << ": ";
		cin >> this->breed;
	}

	string getName()
	{
		return this->name;
	}

	int getAge()
	{
		return this->age;
	}

	string getBreed()
	{
		return this->breed;
	}
};

#endif
