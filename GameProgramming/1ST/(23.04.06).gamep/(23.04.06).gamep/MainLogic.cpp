#include <iostream>
#include <Windows.h>
#include "MainLogic.h"
#include "console.h"
using namespace std;

void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos)
{
	SetConsoleTitle(TEXT("My Bombman"));
	Cursorset(false, 1);
	_pStartPos->x = 0;
	_pStartPos->y = 0;
	_pEndPos->x = 19;
	_pEndPos->y = 13;
	_pPlayer->tPos = *_pStartPos;
	_pPlayer->iBombPower = 1;
	_pPlayer->bTrans = false;
	_pPlayer->bPushonoff = false;
	strcpy_s(_cMaze[0],  "21111111111111111100");
	strcpy_s(_cMaze[1],  "00000000100100000000");
	strcpy_s(_cMaze[2],  "00000000100100000000");
	strcpy_s(_cMaze[3],  "00000000100100001000");
	strcpy_s(_cMaze[4],  "00000000100100001000");
	strcpy_s(_cMaze[5],  "00011111100100001000");
	strcpy_s(_cMaze[6],  "00000000100000001000");
	strcpy_s(_cMaze[7],  "00000000111111111000");
	strcpy_s(_cMaze[8],  "00000000100000001000");
	strcpy_s(_cMaze[9],  "00000000100000001000");
	strcpy_s(_cMaze[10], "00000000100000001000");
	strcpy_s(_cMaze[11], "00000000100000000000");
	strcpy_s(_cMaze[12], "00000000100000000000");
	strcpy_s(_cMaze[13], "00000001111111111000");
	strcpy_s(_cMaze[14], "00000001000000001000");
	strcpy_s(_cMaze[15], "00000001000000001000");
	strcpy_s(_cMaze[16], "00000001000000001000");
	strcpy_s(_cMaze[17], "00000001111000001000");
	strcpy_s(_cMaze[18], "00000000000000001130");
	strcpy_s(_cMaze[19], "00000000000000000000");
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			//플레이어
			//벽
			if (_cMaze[i][j] == '0')
				cout << '■';
			else if (_cMaze[i][j] == '1')
				cout << "   ";
		}
	}
}
