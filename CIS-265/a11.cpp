/*
CIS-165-097WB
Domenico Maisano
Prof. Wang
Project 11
Due by 8/10/17
*/

/*
Steps
1. Input:
    a. prompt user to enter 10 int values which will be stored into an array

2. Processing:
    a. largest = values[0]
    // setting the default value of the largest int to the first element in the array
    b. if(value[n] > largest) {
         largest = value[n] 
         // if there is a value greater than the previous in the array, it will become the largest int
       }

    c. smallest = values[0]
    // setting the default value of the smallest int to the first element in the array
    d. if(value[n] < largest) {
      smallest = value[n] 
      // if there is a value less than the previous in the array, it will become the smallest int
    }

3. Output:
    a. Largest value: someValue
    b. Smallest value: someValue
*/

#include <iostream>
using namespace std;

int main()
{
	int userValues[10];

	for (int i = 0; i < 10; i++)
	{
		cout << "Enter value " << i + 1 << ": ";
		cin >> userValues[i];
	}

	int largest = userValues[0];

	for (int j = 0; j < 10; j++)
	{
		if (userValues[j] > largest)
		{
			largest = userValues[j];
		}
	}

	int smallest = userValues[0];

	for (int k = 0; k < 10; k++)
	{
		if (userValues[k] < smallest)
		{
			smallest = userValues[k];
		}
	}

	cout << "\nLargest value: " << largest << "\nSmallest value: " << smallest;

	return 0;
}
