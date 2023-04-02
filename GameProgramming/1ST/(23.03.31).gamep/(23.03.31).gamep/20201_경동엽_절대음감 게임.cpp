#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <random>
using namespace std;

enum Sound
{
	Do = 1,
	Le,
	Mi,
	Pa,
	Sol,
	Ra,
	Si,
	DoU
};

const float fArray[8] = { 523.25f, 587.33f, 659.26f, 698.46f, 783.99f, 880, 987.77f, 1046.5f };

void Render();

void SoundOut();

void StrOut(int index);

int RandomSound();

int main()
{
	srand((unsigned)time(NULL));

	while (1)
	{
		Render();
		SoundOut();
		Sleep(1000);
		cout << "\n===================\n";

		cout << "\r " << "3 . . .";
		Sleep(1000);
		cout << "\r " << "2 . . .";
		Sleep(1000);
		cout << "\r " << "1 . . .";
		Sleep(1000);
		system("cls");
		cout << "!!!�غ�!!!\n";
		int iIndex = RandomSound();
		if (iIndex == 0)
			return 1;
	}

}

void Render()
{
	cout << "===================\n";
	cout << " | ���� ���� ���� | \n";
	cout << "===================\n";
	cout << "���� : ó���� 8���踦 ����ְ�,\n������ 8�� �� �� ���� ���� ����ش�.\n�׸��� ���� ��ȣ�� ������.\n";
	cout << "===================\n";
	cout << "�غ��ϰ� �ƹ� Ű�� ������.\n";
	while (1)
	{
		if (_kbhit)
		{
			char ch = _getch();
			break;
		}
	}
	cout << "===================\n\n";
}

void SoundOut()
{
	for (int i = 0; i < 8; ++i)
	{
		Beep(fArray[i], 500);
		StrOut(i);
	}
}

void StrOut(int index)
{
	switch (index)
	{
	case 0:
		cout << " ��(1) ";
		break;
	case 1:
		cout << " ��(2) ";
		break;
	case 2:
		cout << " ��(3) ";
		break;
	case 3:
		cout << " ��(4) ";
		break;
	case 4:
		cout << " ��(5) ";
		break;
	case 5:
		cout << " ��(6) ";
		break;
	case 6:
		cout << " ��(7) ";
		break;
	case 7:
		cout << " ��(8)";
		break;
	default:
		break;
	}
}

int RandomSound()
{
	int randomIndex = rand() % 8;
	Beep(fArray[randomIndex], 500);
	while (1)
	{
		if (_kbhit)
		{
			char ch = _getch();
			if (ch == randomIndex+49)
			{
				cout << "�� �ϼ̽��ϴ�.\n";
				cout << "������ ����ұ��? (Y/N) \n";
				while (1)
				{
					if (_kbhit)
					{
						char Index = _getch();
						if (Index == 'Y')
						{
							system("cls");
							return 1;
						}
						return 0;
					}
				}
			}
			else
			{
				cout << "Ʋ���̽��ϴ�\n";
				return 0;
			}
		}
	}

	return 0;
}