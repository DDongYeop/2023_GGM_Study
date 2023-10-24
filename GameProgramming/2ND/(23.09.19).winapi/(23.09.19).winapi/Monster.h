#pragma once
#include "Object.h"
class Monster :
    public Object
{
public:
    Monster();
    ~Monster();
    void Update() override;
public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDis(float _f) { m_fMaxDis = _f; }
    const float& GetSPeed() const { return m_fSpeed; }
private:
    float m_fSpeed;     //스피드
    Vec2 m_vCenterPos;    //중심위치
    float m_fMaxDis;    //이동할 수 있는 최대거리
    float m_fDir;       //방향
    int m_iHp;          //체력
};

