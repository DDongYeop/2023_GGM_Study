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

	//엔진 변수들 초기화
	m_timer = make_shared<Timer>();
	if (m_timer)
		m_timer->Init();

	m_input = make_shared<Input>();
	if (m_input)
		m_input->Init(m_hWnd);

	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(SoundManager)->Init();

	Init();
}

void DONGEngine::MainUpdate()
{
	if (!m_timer)
		return;
	m_timer->Update();
	UINT fps = m_timer->GetFps();

	WCHAR text[100] = _T("");
	::wsprintf(text, _T("FPS : %d"), fps);
	::SetWindowText(m_hWnd, text);

	if (m_input)
		m_input->Update();

	float fDT = m_timer->GetDeltaTime();

	GET_SINGLE(SceneManager)->Update(fDT);
	GET_SINGLE(SoundManager)->Update(fDT);

	Update(fDT);
}

void DONGEngine::MainRender()
{
	HDC hdc = GetDC(m_hWnd);
	RECT winRect = { 0,0,(LONG)m_nWidth, (LONG)m_nHeight };
	FillRect(m_hBackDC, &winRect, (HBRUSH)COLOR_BACKGROUND);

	GET_SINGLE(SceneManager)->Render(m_hBackDC);

	Render(m_hBackDC);

	BitBlt(hdc, 0, 0, m_nWidth, m_nHeight, m_hBackDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void DONGEngine::Cleanup()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hBackDC);

	GET_SINGLE(SceneManager)->Release();
	GET_SINGLE(SoundManager)->Release();

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
