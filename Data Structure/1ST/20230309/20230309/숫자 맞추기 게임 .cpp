#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	int randomIndex = (rand() % 99) + 1;
	int index = 0, num = 0;

	while (1)
	{
		cout << "������ �����Ͽ� ���ÿ� : ";
		cin >> num;

		if (num > randomIndex)
			cout << "������ ������ �����ϴ�. " << endl;
		else if (num < randomIndex)
			cout << "������ ������ �����ϴ�. " << endl;
		else
			break;
		index++;
	}

	cout << "�����մϴ�. �õ�Ƚ�� == " << index;
}