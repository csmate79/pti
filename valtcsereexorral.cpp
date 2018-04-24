#include <iostream>

using namespace std;

int main()
{
	int a = 2000;
	int b = 28;

	cout << a << " " << b << endl;

	a = a xor b;
	b = a xor b;
	a = a xor b;


	cout << a << " " << b << endl;
	return 0;
}
