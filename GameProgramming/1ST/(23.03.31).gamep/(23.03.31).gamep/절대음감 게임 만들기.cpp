#include <iostream>
#include <Windows.h>
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

float iDo = 523.25f;
float iLe = 587.33f;
float iMi = 659.26f;
float iPa = 698.46f;
float iSol = 783.99f;
float iRa = 880;
float iSi = 987.77f;
float iDoU = 1046.5f;
const float fArray[8] = {iDo, iLe, iMi, iPa, iSol, iRa, iSi, iDoU};

void Render(bool isFirst, int index);

void SoundOut();

void StrOut(int index);

int main()
{
	Render(true, 0);
	SoundOut();
	cout << "===================\n";

	system("cls");
	Render(false, 3);
	Sleep(1000);
	system("cls");
	Render(false, 2);
	Sleep(1000);
	system("cls");
	Render(false, 1);
}

void Render(bool isFirst, int index)
{
	cout << "===================\n";
	cout << " | 절대 음감 게임 | \n";
	cout << "===================\n";
	cout << "설명 : 처음에 8음계를 들려주고,\n다음에 8개 중 한 개의 음을 들려준다.\n그리고 음을 번호로 맞힌다.\n";
	cout << "===================\n";
	cout << "준비하고 아무 키나 누른다.\n";
	cout << "===================\n\n";

	if (!isFirst)
	{
		cout << " 도(1)  레(2)  미(3)  파(4)  솔(5)  라(6)  시(7)  도(8)\n ===================\n";
		cout << " " << index << ". . .";
	}
}

void SoundOut()
{
	for (int i = 0; i < 8; ++i)
	{
		StrOut(i);
		Beep(fArray[i], 500);
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
		cout << " 도(8) \n";
		break;
	default:
		break;
	}
}