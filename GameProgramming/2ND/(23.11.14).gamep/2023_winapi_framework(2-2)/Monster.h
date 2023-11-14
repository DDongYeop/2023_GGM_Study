#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	~Monster();
public:
	void Update() override;
public:
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void SetMoveDis(float _f) { m_fMaxDis = _f; }
	const float& GetSpeed() const { return m_fSpeed; }
private:
	float m_fSpeed; // 몬스터 스피드
	Vec2 m_vCenterPos; // 중심 위치
	float m_fMaxDis; // 이동할 수 있는 최대 거리
	float m_fDir; // 방향(-1: 왼쪽, 1: 오른쪽)
	int   m_iHp; // 체력
};

