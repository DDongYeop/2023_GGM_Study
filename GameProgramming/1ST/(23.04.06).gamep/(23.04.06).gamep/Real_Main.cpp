#include <iostream>
#include <Windows.h>
#include "MainLogic.h"
#include "StartScene.h"
using namespace std;

int main()
{
	char cMaze[VERTICAL][HORIZON] = {};
	PLAYER tPlayer = {};
	POS tStartPos = {};
	POS tEndPos = {};
	Init(cMaze, &tPlayer, &tStartPos, &tEndPos);
	while (true)
	{
		system("cls");
		GameTitle();
		int iMenu = MenuDraw();
		if (iMenu == 0) //���� ����
			break;
		else if (iMenu == 1) //���� ����
			InfoDraw();
		else if (iMenu == 2) //����
		{
			cout << endl << "������ �����մϴ�. " << endl;
			for (int i = 0; i < 3; i++)
			{
				cout << '\r' << 3 - i << "...";
				Sleep(1000);
			}
			return 0;
		}
	}
	//���� ���� ���� 
	//Update();
	Render(cMaze, &tPlayer);
}