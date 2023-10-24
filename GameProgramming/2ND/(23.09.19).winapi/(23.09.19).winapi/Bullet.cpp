#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"

Bullet::Bullet() : m_fDir(-1.f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos.y += 500.f * fDT * m_fDir;
	SetPos(vPos);
}
