#include <iostream>
using namespace std;

struct node {
  int data;
  node *next; // recursively creates a new "STRUCT node" pointer
};

class list {

private:
  node *head, *tail;
  // head = front of linked list
  // tail = rear of linked list
public:
  list() {
    head = NULL;
    tail = NULL;
  }

  void printList() {
    node *temp = new node;
    temp = head;
    int count = 0;
    
    while(temp != NULL) {
      cout << "Element: " << count << ",  Value: " << temp->data << "\n";
      temp = temp->next;
      count++;
    }
  }

  void createNode(int value) {
    node *temp = new node;
    temp->data = value; // assigns the arg to the 
    temp->next = NULL; // creating a new node in the list sets it as the top hence 'NULL'

    if(head == NULL) { // if there are no items in the list, set the temp item as the top hence 'NULL'
      head = temp;
      tail = temp;
      temp = NULL;
    }

    else { // if there are item(s) in the list, set temp as the last item in the list aka 'tail'
      tail->next = temp;
      tail = temp;
    }
  }

  void insertHead(int value) {
    node *temp = new node;
    temp->data = value;
    temp->next = head;
    head = temp;
  }

  void insertPos(int value, int pos) {
    node *pre = new node;
    node *cur = new node;
    node *temp = new node; // new node that will be inserted between the pre and cur nodes

    for(int i = 1; i < pos; i++) { // iterates through the list until the node before the desired is found
      pre = cur;
      cur = cur->next;
    }

    temp->data = value;
    pre->next = temp;
    temp->next = cur;
  }

  void deleteHead() {
    node *temp = new node;
    temp = head; // the new node is set as the head
    head = head->next; // the head now becomes the next node in the list

    delete temp; // the original head is dereferenced in memory and is deleted
  }
};

int main() {
  list Foo;

  return 0;
}
