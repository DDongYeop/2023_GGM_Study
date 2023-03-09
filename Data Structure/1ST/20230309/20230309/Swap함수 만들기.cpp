#include <iostream>

using namespace std;

void Swap(int&, int&);
void Swap(int*, int*);

int main()
{
	//����
	int x = 1, y = 3;
	cout << x << " " << y << endl;
	Swap(x, y);
	cout << x << " " << y << endl;

	cout << endl;

	//������
	int a = 1, b = 3;
	cout << a << " " << b << endl;
	Swap(&a, &b);
	cout << a << " " << b << endl;

}

void Swap(int& x, int& y)
{
	int index = x;
	x = y;
	y = index;
}

void Swap(int *x, int *y)
{
	int index = *x;
	*x = *y;
	*y = index;
}