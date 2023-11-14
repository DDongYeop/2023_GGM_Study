#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"
void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false});
	}
	m_ptMouse = {};
}

void KeyMgr::Update()
{
	HWND hWnd = GetFocus();
//	HWND hMainHwnd = Core::GetInst()->GetHwnd();
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			// 키가 눌렸다.
			if (GetAsyncKeyState(m_arrVKKey[i]))
			{
				// 이전에 눌렸어
				if (m_vecKey[i].IsPrevCheck)
				{
					m_vecKey[i].eState = KEY_STATE::PRESS;
				}
				else // 이전에 안눌렸어. 지금 딱!!! 누름
				{
					m_vecKey[i].eState = KEY_STATE::DOWN;
				}
				m_vecKey[i].IsPrevCheck = true;
			}
			// 키가 안눌렸다.
			else
			{
				// 이전에 눌려있었다.
				if (m_vecKey[i].IsPrevCheck)
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
		GetCursorPos(&m_ptMouse); // 마우스 커서 좌표 받기
		// 우리가 가진 윈도우 창 기준으로 좌표 변경
		ScreenToClient(Core::GetInst()->GetHwnd(), &m_ptMouse);
	}

	// 포커싱 해제 alt + tap
	else
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			m_vecKey[i].IsPrevCheck = false;
			if (m_vecKey[i].eState == KEY_STATE::PRESS ||
				m_vecKey[i].eState == KEY_STATE::DOWN)
				m_vecKey[i].eState = KEY_STATE::UP;

			if (m_vecKey[i].eState == KEY_STATE::UP)
				m_vecKey[i].eState = KEY_STATE::NONE;
		}
	}
	

}
