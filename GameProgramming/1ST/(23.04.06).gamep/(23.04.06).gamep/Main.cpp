#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include "console.h"
using namespace std;

int main()
{
	FullScreen();
	{
		//����
		//system("calc");
	
		//��Ʈ�е�
		//system("notepad");
	
		//�̸� �ٲٱ�
		//system("Title 2-2 Bombman");
		//SetConsoleTitle(TEXT("Kyung Dongyeop"));
	
		//ũ�� �ٲٱ�, WIN 11 �� �ٲ�
		//system("mode con cols=50 lines=50");
		//system("mode con cols=50 lines=50 | �̸� �ٲٱ�");

		//����
		//exit(0);

		//���߱�
		//system("pause");
	}

	{
		/*Gotoxy(10, 10);

		SetColor(14, 7);
		cout << "I wnat go home";

		Cursorset(false, 1);*/
	}

	{
	/*	Gotoxy(10, 10);
		cout << "Hello World!";
		Sleep(1000);
		int oldcolor = GetColor() | (GetbgColor() << 4);
		for (int i = 0; i < 16; ++i)
		{
			Gotoxy(i, i);
			SetColor(i, 0);
			cout << "color number : ";
			SetColor(oldcolor, oldcolor >> 4);
			cout << i;
		}*/
	}
	
	int test;
	int x = 0, y = 0;
	int beforex = 0, beforey = 0;
	
	// ��ũ�� ���� �� �ϰ� ��11 �ȵ�
	HWND console = GetConsoleWindow();
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & WS_SIZEBOX);
	RECT rt;
	GetWindowRect(console, &rt);
	while (false)
	{
		//if (_kbhit())
		//{
		//	test = _getch();
		//	if (test == 224)
		//	{
		//		test = _getch();
		//		switch (test)
		//		{
		//		case 72:
		//			//cout << "����" << endl;
		//			y--;
		//			break;
		//		case 75:
		//			//cout << "����" << endl;
		//			x--;
		//			break;
		//		case 77:
		//			//cout << "������" << endl;
		//			x++;
		//			break;
		//		case 80:
		//			//cout << "�Ʒ���" << endl;
		//			y++;
		//			break;
		//		}
		//	}
		//	GotoxyPlayer(x, y);
		//	_putch('a');
		//}

		if (GetAsyncKeyState(VK_UP)	   & 0x8000) y--;
		if (GetAsyncKeyState(VK_DOWN)  & 0x8000) y++;
		if (GetAsyncKeyState(VK_LEFT)  & 0x8000) x--;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x++;
		Sleep(50);
		BOOL result = GotoxyTest(x, y);
		if (result == FALSE)
		{
			x = beforex;
			y = beforey;
			continue;
		}
		else
		{
			beforex = x;
			beforey = y;
		}
		GotoxyPlayer(x, y);
		_putch('a');
	}

	int a;
	while (true)
	{
		cout << "���ڸ� �Է��ϼ���. " << endl;
		cin >> a;
		if (cin.fail())
		{
			cout << "�� �������� ���� " << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			// clear(), ignore()
		}
		cout << a << endl;
	}

	_getch();
}
