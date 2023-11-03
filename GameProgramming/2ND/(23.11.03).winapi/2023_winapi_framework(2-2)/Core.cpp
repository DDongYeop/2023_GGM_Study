#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	// === 변수 초기화 === 
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hbackDC = 0;
	m_hbackbit = 0;

	// 더블버퍼링
	m_hDC = GetDC(m_hWnd);	
	// 1. 생성
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hbackDC = CreateCompatibleDC(m_hDC);

	// 2. 연결
	SelectObject(m_hbackDC, m_hbackbit);

//	m_obj.SetPos(Vec2({ m_ptResolution.x / 2, m_ptResolution.y / 2 }));
////	m_obj.m_ptPos = ;
//	m_obj.SetScale(Vec2(150, 150));

	// ==== Manager Init ====
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();

	return true;
}

void Core::GameLoop()
{
	static int count = 0;
	++count;
	static int prev = GetTickCount64();
	int cur = GetTickCount64();
	if (cur - prev > 1000)
	{
		prev = cur;
		count = 0;
	}
	Update();
	Render();
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hbackDC); // createdc 한거 지우는거
	DeleteObject(m_hbackbit); // createbit 한거 지우는거
}

void Core::Update()
{
	// === Manager Update === 
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();
//	Vec2 vPos = m_obj.GetPos();
//
////	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
////	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)
//	if(KEY_UP(KEY_TYPE::LEFT))
//	{
////		m_obj.m_ptPos.x -= 1;
//		vPos.x -= 100.f;// *fDT;
//	}
//
////	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	if(KEY_DOWN(KEY_TYPE::RIGHT))
//	{
////		m_obj.m_ptPos.x += 1;
//		vPos.x += 100.f * fDT;
//	}
//	m_obj.SetPos(vPos);
}

void Core::Render()
{
	// 칠한다.
	//Rectangle(m_hbackDC, -1,-1,m_ptResolution.x +1,m_ptResolution.y + 1);
	PatBlt(m_hbackDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);

	SceneMgr::GetInst()->Render(m_hbackDC);
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, m_hbackDC);*/

	//// cursor test
	//POINT mousepos = KeyMgr::GetInst()->GetMousePos();
	//static wchar_t mousebuf[100] = {};
	//swprintf_s(mousebuf, L"Mouse: x %d, y: %d", mousepos.x, mousepos.y);
	//TextOut(m_hbackDC, 10, 10, mousebuf, wcslen(mousebuf));

	// 3. 옮긴다.
	BitBlt(m_hDC, 0,0, m_ptResolution.x, m_ptResolution.y, 
		m_hbackDC, 0,0, SRCCOPY);


	//TransparentBlt();
	//StretchBlt();
	// 
	//RECT_RENDER(m_obj.m_ptPos.x, m_obj.m_ptPos.y, m_obj.m_ptScale.x, m_obj.m_ptScale.y, m_hDC);
	//Rectangle(m_hDC
	//	, m_obj.m_ptPos.x - ERROR_CANT_CROSS_RM_BOUNDARY,50,150,150);
}
