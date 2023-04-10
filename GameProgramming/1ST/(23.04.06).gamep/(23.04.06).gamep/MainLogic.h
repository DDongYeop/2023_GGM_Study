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
}BOOM, *PBOOM;
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos);
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer);