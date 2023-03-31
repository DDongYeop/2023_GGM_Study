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
	cout << " | ���� ���� ���� | \n";
	cout << "===================\n";
	cout << "���� : ó���� 8���踦 ����ְ�,\n������ 8�� �� �� ���� ���� ����ش�.\n�׸��� ���� ��ȣ�� ������.\n";
	cout << "===================\n";
	cout << "�غ��ϰ� �ƹ� Ű�� ������.\n";
	cout << "===================\n\n";

	if (!isFirst)
	{
		cout << " ��(1)  ��(2)  ��(3)  ��(4)  ��(5)  ��(6)  ��(7)  ��(8)\n ===================\n";
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
		cout << " ��(8) \n";
		break;
	default:
		break;
	}
}