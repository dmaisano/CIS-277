#include <iostream>
using namespace std;

class Queue {

private:
  int *data, size, front, rear;

public:

  Queue(int s) {
    front = rear = -1;
    size = s;
    data = new int[s];
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
    else if(front != 0 && rear == size - 1) {
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
      return NULL;
    }

    return num;
  }
};

int main() {
  Queue q(10);
  
  
  return 0;
}
