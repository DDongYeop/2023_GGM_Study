#include <iostream>
#include <windows.h>

using namespace std;

enum Level { EASY = 1, NORMAL, HARD};

int main()
{
	cout << "====================================\n";
	cout << "���� ��� �����Դϴ�. ��带 �����ϼ���\n";
	cout << "  EASY : 1   NORMAL : 2    HARD : 3  \n";
	cout << "====================================\n";
	int index, iInput;
	cin >> index;
	system("cls");
	switch (index) // {}����ϸ� ���� �� �� �ִ� 
	{
	case EASY:
	{
		int iNumber[EASY * 5] = {};
		for (int i = 0; i < EASY * 5; i++) //�̾Ƴ�
			iNumber[i] = rand() % +1;

		for (int i = 0; i < EASY * 5; i++)
		{
			cout << iNumber[i] << " ";
			Sleep(1000);
		}
		system("cls");
		cout << "EASY��� �Դϴ�. ��� �� ���ڸ� �Է��ϼ���. : " << endl;
		for (int i = 0; i < EASY * 5; i++)
		{
			cin >> iInput;
			if (iNumber[i] != iInput)
				cout << "�� Ʋ�Ƚ��ϴ�. ";
		}
	}
		break;
	case NORMAL:
	{
	}
		break;
	case HARD:
	{
	}
		break;
	}
}


//�̰͵� �Լ��� �ٲ����