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

	Gotoxy(10, 10);

	_getch();
}
