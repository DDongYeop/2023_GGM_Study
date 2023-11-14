#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
Monster::Monster()
	: m_fSpeed(100.f)
	, m_fMaxDis(50.f)
	, m_vCenterPos(Vec2(0.f,0.f))
	, m_fDir(1.f) // 오른쪽부터 이동
	, m_iHp(5)
{
	CreateCollider();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vCurPos = GetPos();
	vCurPos.x += m_fSpeed * fDT * m_fDir;
	
	// 내가 갈 수 있는 거리 최대로 갔냐? => 방향 바꿔줄거야.
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDis;
	if (fDist > 0.f)
	{
		// dir 바꾸기
		m_fDir *= -1;
		vCurPos.x += fDist * m_fDir;
	}
	SetPos(vCurPos);
}
