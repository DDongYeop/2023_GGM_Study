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

void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<BOOM>& _vecBomb, vector<POS>& _boomEffect)
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

	if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != '0') //벽이 아니면 갱신
	{
		_pPlayer->tPos = _pPlayer->tNewPos;
	}

	if (Getitem(_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x], _pPlayer))
		_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] = '1';

	//슬라임, 푸쉬 능력 구현
	else if (_pPlayer->bPushonoff && _pPlayer->bWallPush && _cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] == '0')
	{
		POS tDiffpos = {_pPlayer->tNewPos.x - _pPlayer->tPos.x, _pPlayer->tNewPos.y - _pPlayer->tPos.y}; 
		POS tNextpos = { _pPlayer->tPos.x + tDiffpos.x * 1, _pPlayer->tPos.y + tDiffpos.y * 1 }; //다음칸
		POS tDoubleps = { _pPlayer->tPos.x + tDiffpos.x * 2, _pPlayer->tPos.y + tDiffpos.y * 2 }; //다다음칸
		
		if (_cMaze[tDoubleps.y][tDoubleps.x] == '0' && _pPlayer->bTrans) //푸쉬 ON, 다음다음이 벽
		{
			_pPlayer->tPos = _pPlayer->tNewPos;
		}
		else if (_cMaze[tDoubleps.y][tDoubleps.x] == '1') //푸쉬 ON, 다음다음이 길이
		{
			_cMaze[tDoubleps.y][tDoubleps.x] = '0';
			_cMaze[tNextpos.y][tNextpos.x] = '1';
			_pPlayer->tPos = _pPlayer->tNewPos;
		}
	}
	else if (_pPlayer->bTrans)
	{
		_pPlayer->tPos = _pPlayer->tNewPos;
	}

	// 폭탄설치
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		BombCreate(_cMaze, _pPlayer, _vecBomb);

	int iBombcount = _pPlayer->iBombCount;
	for (int i = 0; i < iBombcount; i++)
	{
		BOOM& boomItem = _vecBomb[i]; //폭탄 들고 온다
		boomItem.life--; // 점점 life감소 시킨다
		//깜빡거리는거
		boomItem.life % 10 >= 5 ? _cMaze[boomItem.y][boomItem.x] = 'b' : _cMaze[boomItem.y][boomItem.x] = 'p';
		if (boomItem.life <= 0) //폭탄이 터져야함
		{
			boomItem.bDie = true;
			--_pPlayer->iBombCount;
			Fire(_cMaze, _pPlayer, { boomItem.x, boomItem.y }, _boomEffect);
			//길로 바꿔줘야함
			//터트린다
		}
	}
}

void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& _boomEffect)
{
	_cMaze[_boompos.y][_boompos.x] = '1';
	//폭탄 범위
	int iBombminrangex = _boompos.x - _pPlayer->iBombPower;
	int iBombmaxrangex = _boompos.x + _pPlayer->iBombPower;
	int iBombminrangey = _boompos.y - _pPlayer->iBombPower;
	int iBombmaxrangey = _boompos.y + _pPlayer->iBombPower;

	//플레이어 확인
	if ((_pPlayer->tPos.x >= iBombminrangex && _pPlayer->tPos.x <= iBombmaxrangex && _pPlayer->tPos.y == _boompos.y) ||
		(_pPlayer->tPos.y >= iBombminrangey && _pPlayer->tPos.y <= iBombmaxrangey && _pPlayer->tPos.x == _boompos.x))
		_pPlayer->tPos = {0,0};

	//폭탄 이펙트
	static vector<POS> veceffect;
	for (int i = iBombminrangex; i <= iBombmaxrangex; ++i)
	{
		veceffect.push_back({ clamp(i, 0, HORIZON - 2), _boompos.y });
	}
	for (int i = iBombminrangey; i <= iBombmaxrangey; ++i)
	{
		veceffect.push_back({ _boompos.x, clamp(i, 0, VERTICAL - 1) });
	}

	//길로 바꿔주는 과정에서 아이템 확률
	//반복문을 돌면서 veceffect를 가지고 반복문 돌면서 우리가 길로 바꾸고 확률 지정
	for (const auto& target : veceffect)
	{
		_boomEffect.push_back(target); 
		if (_cMaze[target.y][target.x] == '0')
		{
			float fRandom = rand() % 10001 / 100.f; // 0 ~ 10000 -> 0.0 ~ 100%
			if (fRandom <= 50.f)
			{
				float fRandomitem = rand() % 10001 / 100.f; 
				if (fRandomitem <= 50.f)
					_cMaze[target.y][target.x] = '4'; //물풍선
				if (fRandomitem <= 70.f)
					_cMaze[target.y][target.x] = '5'; //슬라임
				else 
					_cMaze[target.y][target.x] = '6'; //푸시
			}
			else
				_cMaze[target.y][target.x] = '1'; 
		}
	}
	veceffect.clear();
}

void Event(std::vector<BOOM>& _vecBomb, std::vector<POS>& _boomEffect)
{
	vector<BOOM>::iterator iter = _vecBomb.begin();
	for (; iter != _vecBomb.end();)
	{
		if (iter->bDie)
			iter = _vecBomb.erase(iter);
		else
			iter++;
	}

	vector<POS>::iterator effectiter = _boomEffect.begin();
	for (; effectiter != _boomEffect.end();)
	{
		effectiter = _boomEffect.erase(effectiter);
	}
}

bool Getitem(char _cItem, PPLAYER _pPlayer)
{
	if (_cItem == '4') //물풍선 파워
	{
		_pPlayer->iBombPower++;
		return true;
	}
	if (_cItem == '5') //슬라임
	{
		_pPlayer->bTrans = true;
		return true;
	}
	if (_cItem == '6') //푸시
	{
		_pPlayer->bWallPush = true;
		_pPlayer->bPushonoff = true;
		return true;
		
	}
	return FALSE;
}

void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, vector<POS>& _boomEffect)
{
	for (int i = 0; i < VERTICAL; i++)
	{
		for (int j = 0; j < HORIZON; j++)
		{
			bool drawed = false; //아직 그려지지 않음
			for (int k = 0; i < _boomEffect.size(); ++k)
			{
				if (_boomEffect[k].y == i && _boomEffect[k].x == j)
				{
					SetColor((int)COLOR::LIGHT_BLUE, (int)COLOR::BLACK);
					cout << "▤";
					_boomEffect.erase(_boomEffect.begin() + k);
					drawed = true;
					break;
				}
			}
			if (drawed)
				continue;
			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
			if (_pPlayer->tPos.x == j && _pPlayer->tPos.y == i)
				cout << "§";
			else if (_cMaze[i][j] == '0')
				cout << "■";
			else if (_cMaze[i][j] == '1')
				cout << " ";
			else if (_cMaze[i][j] == '2')
				cout << "®";
			else if (_cMaze[i][j] == '3')
				cout << "♨";
			else if (_cMaze[i][j] == 'b') //물풍선
			{
				SetColor((int)COLOR::SKYBLUE, (int)COLOR::BLACK);
				cout << "＠";
			}
			else if (_cMaze[i][j] == 'p')
			{
				SetColor((int)COLOR::MINT, (int)COLOR::BLACK);
				cout << "○";
			}
			else if (_cMaze[i][j] == '4') //물풍선
				cout << "◐";
			else if (_cMaze[i][j] == '5') //슬라임
				cout << "♤";
			else if (_cMaze[i][j] == '6') //푸쉬
				cout << "※";
			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
		}
		cout << '\n';
	}

	cout << "SPACEBAR : 폭탄설치, E: 푸시능력 ON/OFF" << endl;
	cout << "폭탄 파워" << _pPlayer->iBombPower << endl; // ->, (*iBombPower).
	if (_pPlayer->bPushonoff)
		cout << "푸시 능력" << "ON " << endl;
	else
		cout << "푸시 능력" << "OFF" << endl;
	if (_pPlayer->bTrans)
		cout << "슬라임 능력" << "ON " << endl;
	else
		cout << "슬라임 능력" << "OFF" << endl;	
}

void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb)
{
	//예외처리 폭탄의 개수는 우리 기획상 5개로 한정
	//종료조건
	if (_pPlayer->iBombCount == 5)
		return;
	//폭탄을 설치
	if (_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] == '1')
	{
		_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] = 'b';
		_pPlayer->iBombCount++;
		_vecBomb.push_back({_pPlayer->tPos.x, _pPlayer->tPos.y, 50, false});
	}
}
