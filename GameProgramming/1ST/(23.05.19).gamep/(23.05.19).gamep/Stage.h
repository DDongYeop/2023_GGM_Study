#pragma once
#include "define.h"

class Stage
{
public:
	Stage();
	~Stage();
private:
	char m_cStage[MAP_Y][MAP_X];
	POINT m_tStart;
	POINT m_tEnd;
public:
	POINT GetStart() { return m_tStart; }
	POINT GetEnd() { return m_tEnd; }
	char GetBlock(int x, int y) { return m_cStage[y][x]; }
public:
	bool Init(char* pFileName); //초기화, 파일 불러오기
	void Render(); //스테이지 그리기
};

