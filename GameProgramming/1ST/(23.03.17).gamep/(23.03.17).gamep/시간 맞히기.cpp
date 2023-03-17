#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
	long long llStartTime = time(NULL);
	cout << "===================" << endl;
	cout << "| 시간 맞히기 게임 |" << endl;
	cout << "===================" << endl << endl;

	cout << "===============================================================" << endl;
	cout << "설명 : 시간을 재는 게임입니다." << endl;
	cout << "처음 key와 나중에 누른 key의 사이의 시간을 10초로 만들어놓았습니다." << endl;
	cout << "===============================================================" << endl << endl;

	cout << "=================" << endl;
	cout << "아무키나 누르세요." << endl;
	cout << "=================" << endl << endl;

	char ch = _getch();

	cout << "시작 !!" << endl;
	while (true)
	{
		if (_kbhit())
		{
			cout << "끝!!!" << endl << endl;
			break;
		}
	}

	if (time(NULL) - llStartTime == 10)
		cout << "당신이 이겼습니다. ";
	else
		cout << "당신이 졌습니다. ";
}
