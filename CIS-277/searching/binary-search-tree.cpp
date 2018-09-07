#include <iostream>
#include <vector>
using namespace std;

struct BST
{
	unsigned int data;
	int leftIndex, rightIndex;
};

void binarySearch(vector<int> nodes)
{
	if (nodes.size() == 0)
	{
		cout << "No items to sort in the tree! Please add items before sorting!\n";
	}

	int middle = nodes.size() / 2;
	sort(nodes.begin(), nodes.end()); // sorts the vector

	for (int i = 0; i < nodes.size(); i++)
	{
		cout << "Value: " << nodes[i] << "\n";
	}
}

int main()
{
	vector<int> toast;
	vector<int> waffles;

	for (int i = 20; i >= 1; i--)
	{
		toast.push_back(i);
	}

	// binarySearch(toast);

	cout << "\n";

	return 0;
}
