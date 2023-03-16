#include <iostream>

using namespace std;

int Fibonacci(int index);

int arrayy[100] = { 0, 1 , };

int main()
{
	cout << Fibonacci(10);
}

int Fibonacci(int index)
{
	if (index < 2)
		return index;
	else
	{
		if (arrayy[index])
			return arrayy[index];
		else
			return arrayy[index] = Fibonacci(index - 1) + Fibonacci(index - 2);
	}
}