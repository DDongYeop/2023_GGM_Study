#include <iostream>
#include <algorithm>
#include <vector>
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
	_pEndPos->x = 18;
	_pEndPos->y = 18;
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

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<BOOM>& _vecBomb, vector<POS> _bombEffect)
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		system("cls");
		exit(0);
	}
	_pPlayer->tNewPos = _pPlayer->tPos;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		--_pPlayer->tNewPos.y;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		++_pPlayer->tNewPos.y;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		--_pPlayer->tNewPos.x;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		++_pPlayer->tNewPos.x;
		Sleep(100);
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		_pPlayer->bPushonoff = !_pPlayer->bPushonoff;
		Sleep(100);
	}

	_pPlayer->tNewPos.x = clamp(_pPlayer->tNewPos.x, 0, HORIZON-2);
	_pPlayer->tNewPos.y = clamp(_pPlayer->tNewPos.y, 0, VERTICAL-1);

	if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != '0') //���� �ƴϸ� ����
	{
		_pPlayer->tPos = _pPlayer->tNewPos;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// ��ź��ġ
		BombCreate(_cMaze, _pPlayer, _vecBomb);
	}

	int iBombcount = _pPlayer->iBombCount;
	for (int i = 0; i < iBombcount; i++)
	{
		BOOM& boomItem = _vecBomb[i];
		boomItem.life--;
	}
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<POS> _boomEffect)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			//�÷��̾�
			//��
			if (_pPlayer->tPos.x == j && _pPlayer->tPos.y == i)
				cout << "��";
			if (_cMaze[i][j] == '0')
				cout << "��";
			else if (_cMaze[i][j] == '1')
				cout << " ";
			else if (_cMaze[i][j] == '2')
				cout << "��";
			else if (_cMaze[i][j] == '3')
				cout << "��";
			else if (_cMaze[i][j] == 'b') //��ǳ��
			{
				SetColor((int)COLOR::SKYBLUE, (int)COLOR::BALCK);
				cout << "��";
			}
			else if (_cMaze[i][j] == 'p')
			{
				SetColor((int)COLOR::MINT, (int)COLOR::BALCK);
				cout << "��";
			}
			else if (_cMaze[i][j] == '4') //������
				cout << "��";
			else if (_cMaze[i][j] == '5') //Ǫ��
				cout << "��";
			SetColor((int)COLOR::WHITE, (int)COLOR::BALCK);
		}
		cout << '\n';
	}

	cout << "SPACEBAR : ��ź��ġ, E: Ǫ�ôɷ� ON/OFF" << endl;
	cout << "��ź �Ŀ�" << _pPlayer->iBombPower << endl; // ->, (*iBombPower).
	if (_pPlayer->bPushonoff)
		cout << "Ǫ�� �ɷ�" << "ON " << endl;
	else
		cout << "Ǫ�� �ɷ�" << "OFF" << endl;
	if (_pPlayer->bTrans)
		cout << "������ �ɷ�" << "ON " << endl;
	else
		cout << "������ �ɷ�" << "OFF" << endl;	
}

void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb)
{
	//����ó�� ��ź�� ������ �츮 ��ȹ�� 5���� ����
	//��������
	if (_pPlayer->iBombCount == 5)
		return;
	//��ź�� ��ġ
	if (_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] == '1')
	{
		_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] = 'b';
		_pPlayer->iBombCount++;
		_vecBomb.push_back({_pPlayer->tPos.x, _pPlayer->tPos.y, 50, false});
	}
}
