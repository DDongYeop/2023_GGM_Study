#include "pch.h"
#include "KeyMgr.h"

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
	m_ptMouse = {};
}

void KeyMgr::Update()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		if (GetAsyncKeyState(m_arrVKKey[i]))
		{
			if (m_vecKey[i].IsPrevCheck) //������ ����
			{
				m_vecKey[i].eState = KEY_STATE::PRESS;
			}
			else //���� �� ����
			{
				m_vecKey[i].eState = KEY_STATE::DOWN;
			}
			m_vecKey[i].IsPrevCheck - true;
		}
		else
		{
			//������ ���� �־���
			if (m_vecKey[i].IsPrevCheck) //������ ����
			{
				m_vecKey[i].eState = KEY_STATE::UP;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
			m_vecKey[i].IsPrevCheck - false;
		}
	}
}
