/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 1
Due by 7/18/17
*/

/*
Steps
1. Input:
    -none

2. Processing:
    a. int num1 = 62, num2 = 99, total = 0;
    b. total = num1 + num2;

3. Output:
    a. total // which has a value of 161
*/

#include <iostream>
using namespace std;

int main()
{
	int num1 = 62, num2 = 99,
			total = 0; // variables declared and initialized with values

	total = num1 + num2; // sum is added and stored in the total variable

	cout << "Total: " << total; // total is logged to the console

	return 0;
}
