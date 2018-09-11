#include <iostream>
using namespace std;

class Queue {

private:
  int *data, front, rear;
  string name;

public:
  int size, max;

  Queue(int num = NULL, string qname = "") {
    if (num == NULL) {
      cout << "Enter the size for the Queue: ";
      cin >> num;
    }

    front = rear = -1;
    size = num;
    max = size - 1;
    data = new int[size];

    if (qname == "") {
      cout << "Enter a name for the Queue: ";
      cin >> qname;
    }

    name = qname;
  }

  void print() {
    if (front == -1) {
      cout << "Queue is empty! Please add items to queue!";
    }

    cout << "Items in Queue '" << name << "'...\n";

    // Executes if the rear is larger than the front (this executes in most
    // cases)
    if (rear >= front) {
      for (int i = front; i <= rear; i++) {
        cout << "Item: " << i << "\tValue: " << data[i] << "\n";
      }
    }

    // Executes if the array is circular and wraps around
    // Example: size = 10, front = 7, rear = 3
    else {
      for (int i = front; i < size; i++) {
        cout << "Item: " << i << "\tValue: " << data[i] << "\n";
        ;
      }

      for (int i = 0; i <= rear; i++) {
        cout << "Item: " << i << "\tValue: " << data[i] << "\n";
      }
    }

    cout << "\n";
  }

  void enqueue(int num) {
    // Displays an error message if the queue is full
    if ((front == 0 && rear == max) || rear == front - 1) {
      cout
          << "Queue is full! Please remove items before adding to the queue!\n";
    }

    // Initializes front/rear and inserts first item
    else if (front == -1 && rear == -1) {
      front = rear = 0;
      data[rear] = num;
    }

    // If rear becomes the last item in the Queue and the front is not zero, set
    // the rear as the front
    else if (front != 0 && rear == max) {
      rear = 0;
      data[rear] = num;
    }

    // Increments the rear and adds the num to the end (rear) of the Queue
    else {
      rear++;
      data[rear] = num;
    }
  }

  int dequeue() {
    int num;

    if (front == -1) {
      cout << "Queue is empty! Please add items to queue before removing!";
      num = NULL; // returns null if the Queue is empty
                  // NULL == 0
    }

    num = data[front];
    data[front] = -1;

    // Executes if there is only one item in the Queue
    if (front == rear) {
      front = rear = -1;
    }

    // Wraps the Queue around itself (circular)
    else if (front == max)
      front = 0;

    // Increments the front if none of two conditions are met
    else
      front++;

    return num;
  }
};

int main() {
  Queue q(5, "Toast");

  // Inserting elements in Circular Queue
  q.enqueue(14);
  q.enqueue(22);
  q.enqueue(13);
  q.enqueue(-6);

  // Display elements present in Circular Queue
  q.print();

  // Deleting elements from Circular Queue
  q.dequeue();
  q.dequeue();

  q.print();

  q.enqueue(9);
  q.enqueue(20);
  q.enqueue(5);

  q.print();
  q.enqueue(20);

  q.dequeue();

  cout << "\n";

  return 0;
}
