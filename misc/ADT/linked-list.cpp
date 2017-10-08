#include <iostream>
using namespace std;

struct node {
  int data;
  node *next; // recursively creates a new "STRUCT node" pointer
};

class list {
  private:
    node *head, *tail;
  public:
    list() {
      head = NULL;
      tail = NULL;
    }
};

void createNode;

int main() {
  list Foo;

  return 0;
}
