/*
CIS-277-601HY
Domenico Maisano
Prof. Aljamal
Linked List Program
*/

#include <iostream>
using namespace std;

struct node
{
	int data;
	node *next; // pointer to the next node in the list
};

class List
{

private:
	node *head, *tail;
	// head = front of linked list
	// tail = rear of linked list
public:
	List()
	{
		head = NULL;
		tail = NULL;
	}

	void print()
	{
		node *temp = new node;
		temp = head;
		int count = 0;

		while (temp != NULL)
		{
			cout << "Element: " << count << ",  Value: " << temp->data << "\n";
			temp = temp->next;
			count++;
		}
	}

	// creates node to end of list
	void createNode(int value)
	{
		node *temp = new node;
		temp->data = value; // assigns the 'value' to the node's data
		temp->next = NULL;	// creating a new node in the list sets it as the top hence 'NULL'

		if (head == NULL)
		{ // if there are no items in the list, set the temp item as the top hence 'NULL'
			head = temp;
			tail = temp;
			temp = NULL;
		}

		else
		{ // if there are item(s) in the list, set temp as the last item in the list aka 'tail'
			tail->next = temp;
			tail = temp;
		}
	}

	// deletes the head node and assigns the next one as the head
	void deleteNode()
	{
		node *temp = new node;
		temp = head;			 // the new node is set as the head
		head = head->next; // the head now becomes the next node in the list

		delete temp; // the original head is dereferenced in memory and is deleted
	}
};

// dummy function to run in class
void demo();

int main()
{

	demo();

	cout << "\n";

	return 0;
}

void demo()
{
	List list;

	list.createNode(10);
	list.createNode(20);
	list.createNode(30);
	list.createNode(40);
	list.createNode(50);
	list.createNode(60);
	list.createNode(70);
	list.createNode(80);
	list.createNode(90);

	cout << "--Initial List--\n";
	list.print();
	cout << "\n\n--Updated List--\n";

	list.deleteNode();
	list.deleteNode();
	list.deleteNode();
	list.deleteNode();

	list.print();
}
