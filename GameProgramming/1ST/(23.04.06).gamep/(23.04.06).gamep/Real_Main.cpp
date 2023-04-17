#include <iostream>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include "console.h"
#include "MainLogic.h"
#include "StartScene.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

int main()
{
	char cMaze[VERTICAL][HORIZON] = {};
	PLAYER tPlayer = {};
	POS tStartPos = {};
	POS tEndPos = {};
	vector<BOOM> vecBomb;
	vector<POS> boomEffect;
	Init(cMaze, &tPlayer, &tStartPos, &tEndPos);
	while (true)
	{
		system("cls");
		GameTitle();
		int iMenu = MenuDraw();
		if (iMenu == 0) //게임 시작
			break;
		else if (iMenu == 1) //게임 정보
			InfoDraw();
		else if (iMenu == 2) //종료
		{
			cout << endl << "게임을 종료합니다. " << endl;
			for (int i = 0; i < 3; i++)
			{
				cout << '\r' << 3 - i << "...";
				Sleep(1000);
			}
			return 0;
		}
	}
	system("cls");
	//게임 로직 시작 
	while (true)
	{
		Gotoxy(0, 0);
		Update(cMaze, &tPlayer, vecBomb, boomEffect);
		Render(cMaze, &tPlayer, boomEffect);
		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			PlaySound(TEXT("pickupCoin.wav"), 0, SND_FILENAME | SND_ASYNC);
			Sleep(1000);
			break;
		}
	}
}