#include "Player.h"

Player::Player()
	: m_tPos {0,8}
{
}

Player::~Player()
{
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		--m_tPos.x;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		++m_tPos.x;
}
