#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include "StartScene.h"
#include "console.h"
using namespace std;

static int x = 30;
static int y = 12;

void GameTitle()
{
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"██████╗  ██████╗ ███╗   ███╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗" << endl;
	wcout << L"██╔══██╗██╔═══██╗████╗ ████║██╔══██╗████╗ ████║██╔══██╗████╗  ██║" << endl;
	wcout << L"██████╔╝██║   ██║██╔████╔██║██████╔╝██╔████╔██║███████║██╔██╗ ██║" << endl;
	wcout << L"██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║" << endl;
	wcout << L"██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║" << endl;
	wcout << L"╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝" << endl;
	int Curmode = _setmode(_fileno(stdout), prevmode);


}

int KeyController()
{
	/*if (GetAsyncKeyState(VK_UP) & 0x8000)
		return (int)KEY::UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		return (int)KEY::DOWN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		return (int)KEY::SPACE;*/

	int iKey = _getch();
	if (iKey == 224)
	{
		iKey = _getch();
		switch (iKey)
		{
		case 72:
			return (int)KEY::UP;
			break;
		case 80:
			return (int)KEY::DOWN;
			break;
		default:
			break;
		}
	}
	else if (iKey == 32)
		return (int)KEY::SPACE;

	return 0;
}

int MenuDraw()
{
	// 게임 시작, 게임 정보, 종료하기 
	Gotoxy(x, y);
	cout << "게임 시작";
	Gotoxy(x, y+1);
	cout << "게임 정보";
	Gotoxy(x, y+2);
	cout << "종료 하기";
	while (true)
	{
		int iKey = KeyController();
		switch (iKey)
		{
		case (int)KEY::UP:
		{
			if (y > 12)
			{
				Gotoxy(x-2, y);
				cout << " ";
				Gotoxy(x-2, --y);
				cout << ">";
			}
		} break;
		case (int)KEY::DOWN:
		{
			if (y < 14)
				if (y < 14)
				{
					Gotoxy(x - 2, y);
					cout << " ";
					Gotoxy(x - 2, ++y);
					cout << ">";
				}
		} break;
		case (int)KEY::SPACE:
		{
			return y - 12;
		} break;
		}
	}
	return 0;
}

void InfoDraw()
{
	system("cls");
	cout << endl << endl;
	cout << "[조작법]" << endl;
	cout << "이동: 방향키" << endl;
	cout << "선택: 스페이스바" << endl;
	cout << "방향키로 움직여 도착지점으로 이동하세요." << endl;
	cout << "게임 시작을 누른 후 스페이스바를 누르면 폭탕니 설치됩니다." << endl;

	while (true)
	{
		if (KeyController() == (int)KEY::SPACE)
			break;
	}
}
