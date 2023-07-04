#include "pch.h"
#include "ProgressBar.h"
#include "Image.h"
#include "ImageManager.h"

ProgressBar::ProgressBar()
{
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_width = 0;
	m_widthGauge = 0;
	m_height = 0;
	m_heightGauge = 0;
	m_horizontal = true;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Init(wstring frontImage, wstring backImage, float x, float y, int width, int height, bool bHori)
{
	m_frontImage = GET_SINGLE(ImageManager)->AddImage(frontImage, frontImage, false);
	m_backImage = GET_SINGLE(ImageManager)->AddImage(backImage, backImage, false);

	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	m_widthGauge = width;
	m_heightGauge = height;
	m_horizontal = bHori;
}

void ProgressBar::Init(shared_ptr<Image> frontImage, shared_ptr<Image> backImage, float x, float y, int width, int height, bool bHori)
{
	m_frontImage = frontImage;
	m_backImage = backImage;

	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	m_widthGauge = width;
	m_heightGauge = height;
	m_horizontal = bHori;
}

void ProgressBar::Update(float dt)
{
}

void ProgressBar::Render(HDC hdc)
{
	if (m_backImage)
	{
		m_backImage->DrawBitmap(hdc, (int)m_posX, (int)m_posY, m_width, m_height);
	}
	if (m_frontImage)
	{
		m_frontImage->DrawBitmap(hdc, (int)m_posX, (int)m_posY, m_widthGauge, m_heightGauge);
	}
}

void ProgressBar::Release()
{
}

void ProgressBar::SetGauge(float currentGauge, float maxGauge)
{
	if (currentGauge > maxGauge)
	{
		currentGauge = maxGauge;
		return;
	}

	if (m_horizontal)
	{
		m_widthGauge = static_cast<int>((currentGauge / maxGauge) * m_width);
	}
	else
	{
		m_heightGauge = static_cast<int>((currentGauge / maxGauge) * m_height);
	}
}

void ProgressBar::SetPosition(float x, float y)
{
	m_posX = x;
	m_posY = y;
}
