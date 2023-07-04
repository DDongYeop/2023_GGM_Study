#include "pch.h"
#include "BackGround.h"

BackGround::BackGround()
	: Actor(0, 0)
{
	m_fScrollY = 0.0f;
	m_fScrollSpeed = 100.0f;
}

BackGround::BackGround(float x, float y, int width, int height, float scale, float scrollY, float scrollSpeed)
	:Actor(x, y, width, height, scale)
{
	m_fScrollY = scrollY;
	m_fScrollSpeed = scrollSpeed;
	m_rcDraw = { (LONG)x, (LONG)y, (LONG)width, (LONG)height };
}

BackGround::~BackGround()
{
}

void BackGround::Init()
{
	m_imageBG = make_shared<Image>();
	if (m_imageBG)
	{
		m_imageBG = GET_SINGLE(ImageManager)->AddImage(L"BG", L"Resources/Image/Background1.bmp", false);

		if (m_nWidth == 0)
			m_nWidth = m_imageBG->GetWidth();
		if (m_nHeight == 0)
			m_nHeight = m_imageBG->GetHeight();
	}
}

void BackGround::Update(float dt)
{
	m_fScrollY += m_fScrollSpeed * dt;

	if (m_fScrollY >= m_nHeight)
		m_fScrollY -= m_nHeight;
}

void BackGround::Render(HDC hdc)
{
	if (m_imageBG)
		m_imageBG->DrawLoopBitmap(hdc, &m_rcDraw, 0, -m_fScrollY);
}

void BackGround::Release()
{
	if (m_imageBG)
		m_imageBG->Release();
}
