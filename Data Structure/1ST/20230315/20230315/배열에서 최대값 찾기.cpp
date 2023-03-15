#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	int x, y = 0;
	for (int i = 0; i < 10; i++)
	{
		x = rand() % 101;
		cout << x << " ";
		if (x > y)
			y = x;
	}

	cout << "\n�ִ밪 = " << y;
}