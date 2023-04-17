#include "pch.h"
#include "DONGEngine.h"

DONGEngine::DONGEngine() : m_hBackDC(NULL), m_hBitmap(NULL)
{
}

DONGEngine::~DONGEngine()
{
}

void DONGEngine::Startup()
{
	g_Engine = shared_from_this();

	HDC hdc = GetDC(m_hWnd);

	m_hBackDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, m_nWidth, m_nHeight);

	SelectObject(m_hBackDC, m_hBitmap);

	ReleaseDC(m_hWnd, hdc);

	Init();
}

void DONGEngine::MainUpdate()
{
	float fDT = 0.0f;
	Update(fDT);
}

void DONGEngine::MainRender()
{
	HDC hdc = GetDC(m_hWnd);
	RECT winRect = { 0,0,(LONG)m_nWidth, (LONG)m_nHeight };
	FillRect(m_hBackDC, &winRect, (HBRUSH)COLOR_BACKGROUND);

	Render(m_hBackDC);

	BitBlt(hdc, 0, 0, m_nWidth, m_nHeight, m_hBackDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void DONGEngine::Cleanup()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hBackDC);

	Release();
}

void DONGEngine::Init()
{
}

void DONGEngine::Update(float dt)
{
}

void DONGEngine::Render(HDC hdc)
{
}

void DONGEngine::Release()
{
}
