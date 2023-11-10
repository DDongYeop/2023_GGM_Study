#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
Bullet::Bullet()
//	: m_fDir(-1.f)
	: m_fTheta(0.f)
	, m_vDir(Vec2(0.f,0.f))
	, m_pTex(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
	CreateCollider();
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
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	//ELLIPSE_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, _dc);
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width,Height, RGB(255,0,255));
	Component_Render(_dc);
}
