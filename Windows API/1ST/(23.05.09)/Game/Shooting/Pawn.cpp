#include "pch.h"
#include "Pawn.h"

Pawn::Pawn() : Actor(0, 0)
{
	m_fSpeed = 100.0f;
	m_fMaxHP = 100;
	m_fHP = m_fHP;
	m_fDamage = 10;
}

Pawn::Pawn(float x, float y, int width, int height, float scale, float speed) : Actor(x, y, width, height, scale)
{
	m_fSpeed = speed;
	m_fMaxHP = 100;
	m_fHP = m_fMaxHP;
	m_fDamage = 10;
}

Pawn::~Pawn()
{
}

void Pawn::Init()
{
}

void Pawn::Update(float dt)
{
}

void Pawn::Render(HDC hdc)
{
}

void Pawn::Release()
{
}

RECT Pawn::GetRect()
{
	RECT rt;
	rt.left = (LONG)(m_fPosX - m_nWidth * m_fScale/2);
	rt.top = (LONG)(m_fPosY - m_nHeight * m_fScale/2);
	rt.right = rt.left + (LONG)(m_nWidth * m_fScale);
	rt.bottom = rt.top + (LONG)(m_nHeight * m_fScale);
	return rt;
}
