#include <iostream>
using namespace std;

// function prototype
int flow(int, int, string);

class MyStack {
public:
  int size; // size of the Stack == string length
private:
  char* data; // char array used in the implementation of the Stack
  char * copy;
  int top; // holds the index of the top of the Stack

public:
	MyStack(string str = "") { // constructor function()
    top = -1; // newly created Stack will have a top of -1 == empty Stack
    data = &str[0u]; // converts string to char array
    copy = &str[0u]; // copy of the array
    size = str.length(); // gets the length of the initial string

    for(int i = size; i >= 0; i--)
      push(data[i]);
  }

	void push(char c) { // appends the num to the top of the Stack
    int flag = flow(top, size, "over");

    if(flag == 1) // exits the function if the Stack overflows
      return;

		data[++top] = c; // increments the top before pushing num
  }
  
	void pop() { // pop item from top of stack
    int flag = flow(top, size, "over");
    
    if(flag == 1) // exits the function if Stack overflows
      return;
    
		top--; // subtracts the "top" index by 1 to create space for more items in the Stack
  }
   
	int top() { // returns the top element in the Stack
    int flag = flow(top, size, "under");
    
    if(flag == 1) // exits the function if Stack underflows
      return -1; // data[top] -1

		return data[top];
	}
 
	int isEmpty() {
    if(top == -1)
      return 1; // returns 1 if the Stack is empty
    
		return 0; // returns 0 if the Stack is empty
  }

  void substring() {

  }

	void print() {
    int flag = flow(top, size, "under");
    
    if(flag == 1) // exits the function if stack underflows
      return;
    
    for(int i = 0; i <= top; i++) { // prints all the elements up to and including the top of the Stack
      cout << "\nIndex:  " << i << "\tValue:  " << data[i];
    }
	}
};

int main() {
  MyStack FMS("1011");

  int x = FMS.size;
  cout << x;

  cout << "\n\n";
  return 0;
}

// function used to check is the stack over/under flows
int flow(int top, int size, string flow) {
  if(top == (size - 1) && flow == "over") { 
    cout << "Stack Overflow! Please pop from the stack!\n";
    return 1; // returns 1 (true) if Stack overflows
  }

  else if(top == -1 && flow == "under") { 
    cout << "Stack Underflow! Please push items to the stack!\n";
    return 1; // returns 1 (true) if Stack underflows
  }

  // returns 0 (false) if Stack does not over/under flow
  return 0;
}
