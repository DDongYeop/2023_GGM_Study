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
    float m_fSpeed;     //���ǵ�
    Vec2 m_vCenterPos;    //�߽���ġ
    float m_fMaxDis;    //�̵��� �� �ִ� �ִ�Ÿ�
    float m_fDir;       //����
    int m_iHp;          //ü��
};

