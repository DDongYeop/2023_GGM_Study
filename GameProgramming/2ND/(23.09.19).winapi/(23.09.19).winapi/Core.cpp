#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

bool Core::Init(HWND _hWnd, POINT _ptResolition)
{
	// ======= ���� �ʱ�ȭ =======
	m_hWnd = _hWnd;
	m_ptResolition = _ptResolition;
	m_hbackDC = 0;
	m_hbackbit = 0;

	//���� ���۸�
	m_hDC = GetDC(m_hWnd);
	// 1.����
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolition.x, m_ptResolition.y);
	m_hbackDC = CreateCompatibleDC(m_hDC);
	// 2.����
	SelectObject(m_hbackDC, m_hbackbit);

	m_obj.SetPos(Vec2({ m_ptResolition.x / 2, m_ptResolition.y / 2 }));
	m_obj.SetScale(Vec2(150, 150));

	// ======= Manager Init ======= 
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();

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
	DeleteDC(m_hbackDC); //createdc�Ѱ� ����°�
	DeleteObject(m_hbackbit); //createbit �Ѱ� ����°�
}

void Core::Update()
{
	// ======= Manager Update ======= 
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();

	Vec2 vPos = m_obj.GetPos();
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)
	{
		//m_obj.m_ptPos.x -= 1;
		vPos.x -= 100.f * fDT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		//m_obj.m_ptPos.x += 1;
		vPos.x += 100.f * fDT;
	}
	m_obj.SetPos(vPos);
}

void Core::Render()
{
	//Rectangle(m_hbackDC, -1, -1, m_ptResolition.x + 1, m_ptResolition.y + 1);
	PatBlt(m_hbackDC, 0, 0, m_ptResolition.x, m_ptResolition.y, WHITENESS);
	Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, m_hDC);
	//RECT_RENDER(m_obj.m_ptPos.x, m_obj.m_ptPos.y, m_obj.m_ptScale.x, m_obj.m_ptScale.y, m_hDC);

	//3. �ű��
	BitBlt(m_hDC, 0,0, m_ptResolition.x, m_ptResolition.y, m_hbackDC, 0,0, SRCCOPY);
}
