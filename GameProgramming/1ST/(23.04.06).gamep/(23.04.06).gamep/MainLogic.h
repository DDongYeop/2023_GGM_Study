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
	POS tNewPos;	// �÷��̾��� �� ��ġ
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
	int bDie;
}BOOM, *PBOOM;

#include <vector> //���ø�Ŭ�����̱⿡ �־�����Ѵ� 
//���ӽ����̽��� �־�����Ѵ�. std::vector�� ����ϱ� ������
//using namespace std; //����� ������ �������. �浹�� ���� ����. ����� �־����� ���ƶ� 
void Init(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos);
void Update(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb, std::vector<POS> _bombEffect);
void Render(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<POS> _boomEffect);
void BombCreate(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb);
void Fire(char _cMaze[VERTICAL][HORIZON], PPLAYER _pPlayer, POS _boompos, std::vector<POS>& _boomEffect);
void Event(std::vector<BOOM>& _vecBomb);
bool Getitem(char _cItem, PPLAYER _pPlayer);