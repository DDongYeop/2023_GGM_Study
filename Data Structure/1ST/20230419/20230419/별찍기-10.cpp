#include <iostream>
using namespace std;

void print(int i, int j, int n);

int main()
{
	int num;
	cin >> num;

	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
			print(i, j, num);
		cout << '\n';
	}
}

void print(int i, int j, int n)
{
	if ((i / n) % 3 == 1 && (j / n) % 3 == 1)
		cout << " "; 
	else if (n < 3)
		cout << "*"; 
	else
		print(i, j, n / 3);
}
