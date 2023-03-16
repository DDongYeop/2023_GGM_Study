#include <iostream>

using namespace std;

int Fibonacci(int index);

int main()
{
	cout << Fibonacci(10);
}

int Fibonacci(int index)
{
	if (index == 0 || index == 1)
		return index;

	return Fibonacci(index - 1) + Fibonacci(index - 2);
}