#include <iostream>
using namespace std;

class Queue {

private:
  int *data, front, rear;
  string name;

public:
  int size;
  int max;

  Queue(int num = NULL, string qname = "") {
    if(num == NULL) {
      cout << "Enter the size of the queue: ";
      cin >> num;
    }

    if(qname == "") {
      cout << "Enter a name for the queue: ";
      cin >> qname;
    }

    name = qname;
    size = num;
    max = size - 1;
    data = new int[size];
    front = rear = -1;

    // Initializes the Queue with NULL values
    for(int i = 0; i < size; i++) {
      data[i] = NULL;
    }
  }

  void enqueue(int num = NULL) {
    if(front == 0 && rear == max) {
      cout << "Queue is full! Please remove items before adding to the queue!\n";
      return;
    }

    if(num == NULL) {
      cout << "Enter a number to add to the queue: ";
      cin >> num;
    }

    // Initializes front/rear and inserts first item
    if(front == -1 && rear == -1) {
      front = rear = 0;
      data[rear] = num;
    }

    // If rear is the second to last item in the queue and the front is not zero, set the rear as the front
    else if(front != 0 && rear == max) {
      rear = 0;
      data[rear] = num;
    }

    // Increments the rear and adds the num to the end of the Queue
    else {
      data[rear] = num;
      rear++;
    }
  }

  int dequeue() {
    int num;
    
    if(front == -1) {
      cout << "Queue is empty! Please add items to queue before removing!";
      num = NULL; // returns null if the Queue is empty
    }

    num = data[front];
    data[front] = NULL;

    // Executes if there is only one item in the queue
    if(front == rear) {
      front = rear = -1;
    }

    // Implements the circularity of the queue
    else if(front == max)
      front = 0;

    // Incremenets the front to iterate through the queue
    else
      front++;

    return num;
  }

  void print() {
    if(front == -1) {
      cout << "Queue is empty! Please add items to queue!";
    }

    cout << "\nItems in Queue '" << name << "':\n";

    if(rear >= front) {
      for(int i = front; i <= rear; i++) {
        cout << "Item: " << data[i] << "\n";
      }
    }

    else {
      for(int i = front; i < size; i++) {
        cout << "Item: " << data[i] << "\n";;
      }

      for(int i = 0; i <= rear; i++) {
        cout << "Item: " << data[i] << "\n";
      }
    }

    cout << "\n";
  }

};

int main() {
  Queue q(10);

  // cout << "Size: " << q.size << "\n";

  // q.enqueue();

  int size = q.size;
  for(int i = 0; i < size; i += 2) {
    q.enqueue(i);
    size += 2;
  }

  q.print();

  cout << "\n";
  
  return 0;
}
