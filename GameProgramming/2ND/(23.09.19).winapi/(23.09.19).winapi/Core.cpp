#include "pch.h"
#include "Core.h"

bool Core::Init(HWND _hWnd, POINT _ptResolition)
{
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);
	m_ptResolition = _ptResolition;
	m_obj.m_ptPos = {m_ptResolition.x / 2, m_ptResolition.y / 2};
	m_obj.m_ptScale= {100, 100};
	return true;
}

void Core::GameLoop()
{
	Update();
	Render();
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
}

void Core::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_obj.m_ptPos.x += 1;
	}
}

void Core::Render()
{
	RECT_RENDER(m_obj.m_ptPos.x, m_obj.m_ptPos.y, m_obj.m_ptScale.x, m_obj.m_ptScale.y, m_hDC);
}
