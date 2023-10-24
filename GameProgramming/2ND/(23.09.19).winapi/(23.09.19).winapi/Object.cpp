#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

Object::Object() : m_vPos{}, m_vScale{}
{
}

Object::~Object()
{
}

void Object::Update()
{
	//if (KEY_PRESS(KEY_TYPE::LEFT))
	//{
	//	//m_obj.m_ptPos.x -= 1;
	//	m_vPos.x -= 100.f * fDT;
	//}
	//if (KEY_PRESS(KEY_TYPE::RIGHT))
	//{
	//	//m_obj.m_ptPos.x += 1;
	//	m_vPos.x += 100.f * fDT;
	//}
}

void Object::Render(HDC _dc)
{
	//Vec2 vPos = m_obj.GetPos();
	//Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
}
