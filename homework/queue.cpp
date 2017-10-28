#include <iostream>
#include <cstdlib>
#include <iomanip> // setw
using namespace std;

class Queue {

private:
  // data is an int pointer that will be reassigned to store the array of data the queue contains
  int *data, front, rear;

public:
  int size, max;
  string name;

  // Class Constructor Method
  Queue(int num = NULL, string qname ="") {
    if(num == NULL) {
      cout << "Enter the size for the Queue: ";
      cin >> num;
    }

    size = num;
    max = size - 1;
    front = rear = -1;
    // creates an array that stores elements of specified size
    data = new int[size];
    
    if(qname == "") {
      cout << "Enter a name for the Queue: ";
      cin >> qname;
    }

    name = qname;
  }

  // Iterates over the queue and prints each item
  void print() {
    if(front == -1) {
      cout << "Queue is empty! Please add items to queue!";
      return;
    }

    cout << "Items in Queue '" << name << "': \n";

    // Executes if the rear is larger than the front (this executes in most cases)
    if(rear >= front) {
      for(int i = front; i <= rear; i++) {
        cout << "Item: " << setw(2) << i << "\tValue: " << setw(2) << data[i] << "\n";
      }
    }

    // Executes if the array is circular and wraps around
    else {
      for(int i = front; i < size; i++) {
        cout << "Item: " << setw(2) << i << "\tValue:" << setw(2) << data[i] << "\n";;
      }

      for(int i = 0; i <= rear; i++) {
        cout << "Item: " << setw(2) << i << "\tValue: " << setw(2) << data[i] << "\n";
      }
    }
  }

  // Appends an item to the end of the queue if there is room
  void enqueue(int num) {
    // Displays an error message if the queue is full
    if( (front == 0 && rear == max) || rear == front - 1) {
      cout << "Queue is full! Please remove items before adding to the queue!\n";
    }

    // Initializes front/rear and inserts first item
    else if(front == -1 && rear == -1) {
      front = rear = 0;
      data[rear] = num;
    }

    // If rear becomes the last item in the Queue and the front is not zero, set the rear as the front
    else if(front != 0 && rear == max) {
      rear = 0;
      data[rear] = num;
    }

    // Increments the rear and adds the num to the end (rear) of the Queue
    else {
      rear++;
      data[rear] = num;
    }
  }

  // Removes an item from the front of the queue
  int dequeue() {
    int num;

    if(front == -1) {
      cout << "Queue is empty! Please add items to queue before removing!";
      num = NULL; // returns null if the Queue is empty
      // NULL == 0
    }

    num = data[front];
    data[front] = -1;

    // Executes if there is only one item in the Queue
    if(front == rear) {
      front = rear = -1;
    }

    // Wraps the Queue around itself (circular)
    else if(front == max)
      front = 0;

    // Increments the front if none of two conditions are met
    else
      front++;

    return num;
  }

  // Function that returns true if the queue is full, false if not
  bool isFull() {
    if( (front == 0 && rear == max) || rear == front - 1)
      return true;

    return false;
  }

  // Function that returns true if the queue is empty, false if not
  bool isEmpty() {
    if(front == -1)
      return true;

    return false;
  }

  // Deletes existing data in the queue and creates a new empty queue
  void purge() {
    front = rear = -1;
    data = new int[size];
  }
};

void menu(Queue q);
void demo();

int main() {

  demo();

  cout << "\n";

  return 0;
}

// Menu function that holds all the valid functions to be called on the queue
void menu(Queue q) {
  int userInput = -999;
  int num = 0;

  while(userInput != -1) {
    cout << "\nEnter -1 to exit the program.\n";

    // if the queue has space prompt user to enter multiple items from the queue
    if(q.isFull() != true) {
      cout << "Enter 1 to add an item to queue '" << q.name << "'\n";
    }

    // if the queue is not empty prompt user to print from queue
    if(q.isEmpty() != true) {
      cout << "Enter 2 to delete an item from queue '" << q.name << "'\n";
      cout << "Enter 3 to purge all items from queue '" << q.name << "'\n";
      cout << "Enter 4 to print all items in queue '" << q.name << "'\n";
    }  

    cout << "\nEnter an option: ";
    cin >> userInput;
    
    // Executes if any errors with the input should be caught
    if(cin.fail() || userInput < -1 || userInput == 0 || userInput > 4 || userInput == 1 && q.isFull() || userInput == 2 && q.isEmpty() || userInput == 3 && q.isEmpty() || userInput == 4 && q.isEmpty() ) {
      cin.clear();
      cin.ignore(10000,'\n');
      cout << "Invalid Input! Try Again.\n";
      menu(q);
    }

    if(userInput == -1)
      break; // exits the menu
      
    else if(userInput == 1) {
      cout << "Enter a number to add to the queue: ";
      cin >> num;
      q.enqueue(num);
      menu(q); // recursively calls the menu function
    }

    if(userInput == 2) {
      num = q.dequeue();
      cout << num << " was removed from the queue.\n";
      menu(q);
    }

    if(userInput == 3) {
      q.purge();
      cout << num << " was removed from the queue.\n";
      menu(q);
    }

    if(userInput == 4) {
      q.print();
      menu(q);
    }

  }
}

// Dummy function that will be executed in class
void demo() {
  int size = 0;

  cout << "Enter a size for the demo Queue: ";
  cin >> size;

  Queue q(size, "demo");
  menu(q);
}
