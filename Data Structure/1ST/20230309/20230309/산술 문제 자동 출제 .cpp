#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	int index, x, y;

	cout << "산술 문제를 자동으로 출제합니다. " << endl;
	
	while (1)
	{
		x = rand() % 101;
		y = rand() % 101;

		cout << x << " + " << y << " = ";

		cin >> index;

		if (index == x + y)
		{
			cout << "맞았습니다." << endl << endl;
			continue;
		}
		else
		{
			cout << "틀렸습니다. ";
			break;
		}
	}
}