#include <iostream>
using namespace std;

int doubledArray(int [], int);

int main() {
	int size = 4;
	int list[size] = {0, 1, 2, 3};
	int arraySize = sizeof(list) / sizeof(list[0]);
	//int size = size of array (in bytes) / size of an element

	doubledArray(list, arraySize);

	return 0;
}

int doubledArray(int list[], int size) {
	int newSize = size * 2;
	int* newList = new int[newSize];

	for(int i = 0; i < newSize; i++) {
		if(i < size) {
			newList[i] = list[i];
		}
		else {
			newList[i] = 0;
		}
	}

	return *newList;
}
