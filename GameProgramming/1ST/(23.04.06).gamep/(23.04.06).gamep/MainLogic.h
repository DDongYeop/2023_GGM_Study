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
	POS tPos;		// �÷��̾� ��ġ
	int iBombCount;	// ��ź ����
	int iBombPower;	// ��ź �Ŀ�
	bool bWallPush;	// �� �б�
	bool bTrans;	// ����ȭ
	bool bPushonoff;// �� �б� ����ġ
}PLAYER, *PPLAYER;

typedef struct _tagboom
{
	int x;
	int y;
	int life;
}BOOM, *PBOOM;
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos);
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer);