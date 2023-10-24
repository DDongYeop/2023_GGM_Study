#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false });
	}
	m_ptMouse = {};
}

void KeyMgr::Update()
{
	HWND hWnd = GetFocus();
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			if (GetAsyncKeyState(m_arrVKKey[i]))
			{
				if (m_vecKey[i].IsPrevCheck) //이전에 눌림
				{
					m_vecKey[i].eState = KEY_STATE::PRESS;
				}
				else //지금 딱 누름
				{
					m_vecKey[i].eState = KEY_STATE::DOWN;
				}
				m_vecKey[i].IsPrevCheck = true;
			}
			else
			{
				//이전에 눌려 있었다
				if (m_vecKey[i].IsPrevCheck) //이전에 눌림
				{
					m_vecKey[i].eState = KEY_STATE::UP;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].IsPrevCheck = false;
			}
		}

		// Mouse 
		GetCursorPos(&m_ptMouse); //마우스 커서 좌표 받기
		//우리가 가진 윈도우 창 기준으로 좌표 변경
		ScreenToClient(Core::GetInst()->GetHwnd(), &m_ptMouse);
	}
	else //포커싱 해제 (alt + tap)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			m_vecKey[i].IsPrevCheck = false;
			if (m_vecKey[i].eState == KEY_STATE::PRESS || m_vecKey[i].eState == KEY_STATE::DOWN)
				m_vecKey[i].eState = KEY_STATE::UP;
			if (m_vecKey[i].eState == KEY_STATE::UP)
				m_vecKey[i].eState = KEY_STATE::NONE;
		}

	}
}
