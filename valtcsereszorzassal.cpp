#include <iostream>

using namespace std;

int main()
{
	int a = 2000;
	int b = 28;

	cout << a << " " << b << endl;

	a = a * b;
	b = a / b;
	a = a / b;


	cout << a << " " << b << endl;
	return 0;
}
