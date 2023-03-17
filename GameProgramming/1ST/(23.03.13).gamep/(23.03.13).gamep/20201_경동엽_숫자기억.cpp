#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

enum Level { EASY = 1, NORMAL=2, HARD=3};

void NumberGame(int iNumber[], Level level);

int main()
{
	srand((unsigned int)time(NULL));
	cout << "====================================\n";
	cout << "���� ��� �����Դϴ�. ��带 �����ϼ���\n";
	cout << "  EASY : 1   NORMAL : 2    HARD : 3  \n";
	cout << "====================================\n";
	int index;
	cin >> index;
	system("cls");
	switch (index) // {}����ϸ� ���� �� �� �ִ� 
	{
	case EASY:
	{
		int iNumber[EASY * 5];
		NumberGame(iNumber, EASY);
	} break;
	case NORMAL:
	{
		int iNumber[NORMAL * 5];
		NumberGame(iNumber, NORMAL);
	} break;
	case HARD:
	{
		int iNumber[HARD * 5];
		NumberGame(iNumber, HARD);
	} break;
	}
}


void NumberGame(int iNumber[], Level level)
{
	int iInput;
	for (int i = 0; i < level * 5; i++) //�̾Ƴ�
		iNumber[i] = rand() % 101;

	for (int i = 0; i < level * 5; i++)
	{
		cout << iNumber[i] << " ";
		Sleep(1000);
	}
	system("cls");
	cout << level << "��� �Դϴ�. ��� �� ���ڸ� �Է��ϼ���. : " << endl;
	for (int i = 0; i < level * 5; i++)
	{
		cin >> iInput;
		if (iNumber[i] != iInput)
		{
			cout << "�� Ʋ�Ƚ��ϴ�. ";
			return;
		}
	}

	cout << "�����Դϴ� !";
}


//�̰͵� �Լ��� �ٲ����