#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	int index, x, y;

	cout << "��� ������ �ڵ����� �����մϴ�. " << endl;
	
	while (1)
	{
		x = rand() % 101;
		y = rand() % 101;

		cout << x << " + " << y << " = ";

		cin >> index;

		if (index == x + y)
		{
			cout << "�¾ҽ��ϴ�." << endl << endl;
			continue;
		}
		else
		{
			cout << "Ʋ�Ƚ��ϴ�. ";
			break;
		}
	}
}