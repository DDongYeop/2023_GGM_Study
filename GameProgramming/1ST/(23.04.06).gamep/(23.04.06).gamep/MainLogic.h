#pragma once

const int HORIZON = 21;
const int VERTICAL = 20;
typedef struct _tagpos
{
	int x;
	int y;
}POS, *PPOS;

typedef struct _tagplayer
{
	POS tPos;		// 플레이어 위치
	POS tNewPos;	// 플레이어의 새 위치
	int iBombCount;	// 폭탄 개수
	int iBombPower;	// 폭탄 파워
	bool bWallPush;	// 벽 밀기
	bool bTrans;	// 투명화
	bool bPushonoff;// 벽 밀기 스위치
}PLAYER, *PPLAYER;

typedef struct _tagboom
{
	int x;
	int y;
	int life;
	int bDie;
}BOOM, *PBOOM;

#include <vector> //템플릿클래스이기에 넣어줘야한다 
//네임스페이스를 넣어줘야한다. std::vector로 사용하기 때문에
//using namespace std; //상당히 많은게 들어있음. 충돌날 수도 있음. 헤더엔 넣어주지 말아라 
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos);
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb, std::vector<POS> _bombEffect);
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<POS> _boomEffect);
void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb);
void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& _boomEffect);
void Event(std::vector<BOOM>& _vecBomb);
bool Getitem(char _cItem, PPLAYER _pPlayer);