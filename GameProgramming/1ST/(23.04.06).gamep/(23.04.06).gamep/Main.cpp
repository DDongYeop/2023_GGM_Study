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
		//계산기
		//system("calc");
	
		//노트패드
		//system("notepad");
	
		//이름 바꾸기
		//system("Title 2-2 Bombman");
		//SetConsoleTitle(TEXT("Kyung Dongyeop"));
	
		//크기 바꾸기, WIN 11 안 바뀜
		//system("mode con cols=50 lines=50");
		//system("mode con cols=50 lines=50 | 이름 바꾸기");

		//끄기
		//exit(0);

		//멈추기
		//system("pause");
	}

	Gotoxy(10, 10);

	_getch();
}
