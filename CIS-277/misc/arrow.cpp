#include <iostream>
using namespace std;

struct Arrow
{
	int num;
};

int main()
{
	Arrow foo;
	foo.num = 100;

	Arrow *ptr = &foo;
	ptr->num = 200;

	cout << "Value: " << foo.num;
	cout << "\nReference: " << ptr->num;

	return 0;
}
