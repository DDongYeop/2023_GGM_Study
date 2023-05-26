#pragma once
#include "define.h"
class Player
{
public:
	Player();
	~Player();
private:
	POINT m_tPos;
public:
	void SetPos(int _x, int _y) { m_tPos.x = _x; m_tPos.y = _y; }
	int GetX() { return m_tPos.x; }
	int GetY() { return m_tPos.y; }
};

