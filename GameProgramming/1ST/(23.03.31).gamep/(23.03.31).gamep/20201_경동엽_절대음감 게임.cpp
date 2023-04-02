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
		cout << "!!!준비!!!\n";
		int iIndex = RandomSound();
		if (iIndex == 0)
			return 1;
	}

}

void Render()
{
	cout << "===================\n";
	cout << " | 절대 음감 게임 | \n";
	cout << "===================\n";
	cout << "설명 : 처음에 8음계를 들려주고,\n다음에 8개 중 한 개의 음을 들려준다.\n그리고 음을 번호로 맞힌다.\n";
	cout << "===================\n";
	cout << "준비하고 아무 키나 누른다.\n";
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
		cout << " 도(1) ";
		break;
	case 1:
		cout << " 레(2) ";
		break;
	case 2:
		cout << " 미(3) ";
		break;
	case 3:
		cout << " 파(4) ";
		break;
	case 4:
		cout << " 솔(5) ";
		break;
	case 5:
		cout << " 라(6) ";
		break;
	case 6:
		cout << " 시(7) ";
		break;
	case 7:
		cout << " 도(8)";
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
				cout << "잘 하셨습니다.\n";
				cout << "게임을 계속할까요? (Y/N) \n";
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
				cout << "틀리셨습니다\n";
				return 0;
			}
		}
	}

	return 0;
}