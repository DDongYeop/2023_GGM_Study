#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
Bullet::Bullet()
//	: m_fDir(-1.f)
	: m_fTheta(0.f)
	, m_vDir(Vec2(0.f,0.f))
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	//vPos.x += 500.f * fDT * m_fDir;
	//vPos.y += 500.f * fDT * m_fDir;
	//vPos.x += 500.f * fDT * cosf(m_fTheta);
	//vPos.y += 500.f * fDT * sinf(m_fTheta);
	vPos.x += 500.f * fDT * m_vDir.x;
	vPos.y += 500.f * fDT * m_vDir.y;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	ELLIPSE_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
}
