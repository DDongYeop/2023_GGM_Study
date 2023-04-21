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

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<BOOM>& _vecBomb, vector<POS> _boomEffect)
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

	if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != '0') //∫Æ¿Ã æ∆¥œ∏È ∞ªΩ≈
	{
		_pPlayer->tPos = _pPlayer->tNewPos;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// ∆¯≈∫º≥ƒ°
		BombCreate(_cMaze, _pPlayer, _vecBomb);
	}

	int iBombcount = _pPlayer->iBombCount;
	for (int i = 0; i < iBombcount; i++)
	{
		BOOM& boomItem = _vecBomb[i]; //∆¯≈∫ µÈ∞Ì ø¬¥Ÿ
		boomItem.life--; // ¡°¡° life∞®º“ Ω√≈≤¥Ÿ
		//±Ù∫˝∞≈∏Æ¥¬∞≈
		boomItem.life % 10 >= 5 ? _cMaze[boomItem.y][boomItem.x] = 'b' : _cMaze[boomItem.y][boomItem.x] = 'p';
		if (boomItem.life <= 0) //∆¯≈∫¿Ã ≈Õ¡Ææﬂ«‘
		{
			boomItem.bDie = true;
			--_pPlayer->iBombCount;
			Fire(_cMaze, _pPlayer, { boomItem.x, boomItem.y }, _boomEffect);
			//±Ê∑Œ πŸ≤„¡‡æﬂ«‘
			//≈Õ∆Æ∏∞¥Ÿ
		}
	}
}

void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& _boomEffect)
{
	_cMaze[_boompos.y][_boompos.x] = '1';
	//∆¯≈∫ π¸¿ß
	int iBombminrangex = _boompos.x - _pPlayer->iBombPower;
	int iBombmaxrangex = _boompos.x + _pPlayer->iBombPower;
	int iBombminrangey = _boompos.y - _pPlayer->iBombPower;
	int iBombmaxrangey = _boompos.y + _pPlayer->iBombPower;

	//«√∑π¿ÃæÓ »Æ¿Œ
	if ((_pPlayer->tPos.x >= iBombminrangex && _pPlayer->tPos.x <= iBombmaxrangex && _pPlayer->tPos.y == _boompos.y) ||
		(_pPlayer->tPos.y >= iBombminrangey && _pPlayer->tPos.y <= iBombmaxrangey && _pPlayer->tPos.x == _boompos.x))
		_pPlayer->tPos = {0,0};

	//∆¯≈∫ ¿Ã∆Â∆Æ
	vector<POS> veceffect;
	for (int i = iBombminrangex; i <= iBombmaxrangex; ++i)
	{
		//veceffect.push_back({ clamp(_boompos.x, 0, HORIZON - 2)}, {clamp()});

	}

	//±Ê∑Œ πŸ≤„¡÷¥¬ ∞˙¡§ø°º≠ æ∆¿Ã≈€ »Æ∑¸

}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<POS> _boomEffect)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			//«√∑π¿ÃæÓ
			//∫Æ
			if (_pPlayer->tPos.x == j && _pPlayer->tPos.y == i)
				cout << "°◊";
			if (_cMaze[i][j] == '0')
				cout << "°·";
			else if (_cMaze[i][j] == '1')
				cout << " ";
			else if (_cMaze[i][j] == '2')
				cout << "¢Á";
			else if (_cMaze[i][j] == '3')
				cout << "¢Õ";
			else if (_cMaze[i][j] == 'b') //π∞«≥º±
			{
				SetColor((int)COLOR::SKYBLUE, (int)COLOR::BALCK);
				cout << "£¿";
			}
			else if (_cMaze[i][j] == 'p')
			{
				SetColor((int)COLOR::MINT, (int)COLOR::BALCK);
				cout << "°€";
			}
			else if (_cMaze[i][j] == '4') //ΩΩ∂Û¿”
				cout << "¢ª";
			else if (_cMaze[i][j] == '5') //«™Ω¨
				cout << "°ÿ";
			SetColor((int)COLOR::WHITE, (int)COLOR::BALCK);
		}
		cout << '\n';
	}

	cout << "SPACEBAR : ∆¯≈∫º≥ƒ°, E: «™Ω√¥…∑¬ ON/OFF" << endl;
	cout << "∆¯≈∫ ∆ƒøˆ" << _pPlayer->iBombPower << endl; // ->, (*iBombPower).
	if (_pPlayer->bPushonoff)
		cout << "«™Ω√ ¥…∑¬" << "ON " << endl;
	else
		cout << "«™Ω√ ¥…∑¬" << "OFF" << endl;
	if (_pPlayer->bTrans)
		cout << "ΩΩ∂Û¿” ¥…∑¬" << "ON " << endl;
	else
		cout << "ΩΩ∂Û¿” ¥…∑¬" << "OFF" << endl;	
}

void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb)
{
	//øπø‹√≥∏Æ ∆¯≈∫¿« ∞≥ºˆ¥¬ øÏ∏Æ ±‚»πªÛ 5∞≥∑Œ «—¡§
	//¡æ∑·¡∂∞«
	if (_pPlayer->iBombCount == 5)
		return;
	//∆¯≈∫¿ª º≥ƒ°
	if (_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] == '1')
	{
		_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] = 'b';
		_pPlayer->iBombCount++;
		_vecBomb.push_back({_pPlayer->tPos.x, _pPlayer->tPos.y, 50, false});
	}
}
