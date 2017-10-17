#include <iostream>
using namespace std;

class Queue {

private:
  int *data, size, front, rear;
  string name;

public:

  Queue(int s, string qname ="") {
    front = rear = -1;
    size = s;
    data = new int[s];
    
    if(qname == "") {
      cout << "Enter a name for the Queue: ";
      cin >> qname;
    }

    name = qname;
  }

  void print() {
    if(front == -1) {
      cout << "Queue is empty! Please add items to queue!";
    }

    cout << "Items in Queue '" << name << "'...\n";

    if(rear >= front) {
      for(int i = front; i <= rear; i++) {
        cout << "Item: " << i << "\tValue: " << data[i] << "\n";
      }
    }

    else {
      for(int i = front; i < size; i++) {
        cout << "Item: " << i << "\tValue: " << data[i] << "\n";;
      }

      for(int i = 0; i <= rear; i++) {
        cout << "Item: " << i << "\tValue: " << data[i] << "\n";
      }
    }

    cout << "\n";
  }

  void enqueue(int num) {
    int max = size - 1;

    // Displays an error message if the queue is full
    if( (front == 0 && rear == max) || rear == front - 1) {
      cout << "Queue is full! Please remove items before adding to the queue!\n";
    }

    // Inserts the first element
    else if(front == -1) {
      front = rear = 0;
      data[rear] = num;
    }

    // If rear is the second to last item in the queue and the front is not zero, set the rear as the front
    else if(front != 0 && rear == max) {
      rear = 0;
      data[rear] = num;
    }

    // Increments the rear and adds the num to the rear
    else {
      rear++;
      data[rear] = num;
    }
  }

  int dequeue() {
    int num;

    if(front == -1) {
      cout << "Queue is empty! Please add items to queue before removing!";
      num = NULL; // returns null if the Queue is empty (raises an error)
    }

    num = data[front];
    data[front] = -1;

    if(front == rear) {
      front = -1;
      rear = -1;
    }

    else if(front == (size - 1) )
      front = 0;

    else
      front++;

    return num;
  }
};

int main() {
  Queue q(5, "Toast");
  /*
  
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
  */

  q.dequeue();
  return 0;
}
