#include "pch.h"
#include "Bullet.h"

Bullet::Bullet() : Actor(0, 0)
{
	m_fSpeed = 200.0f;
	m_fAngle = -90.0f * PI / 180.0f;
}

Bullet::Bullet(float x, float y, int width, int height, float scale, float speed, float angle) : Actor(x, y, width, height, scale)
{
	m_fSpeed = speed;
	m_fAngle = angle;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_imageBullet = make_shared<Image>();
	if (m_imageBullet)
	{
		m_imageBullet = GET_SINGLE(ImageManager)->AddImage(L"Bullet", L"Resources/Image/projectile01_2.bmp");

		if (m_nWidth == 0)
			m_nWidth = m_imageBullet->GetWidth();
		if (m_nHeight == 0)
			m_nHeight = m_imageBullet->GetHeight();
	}
}

void Bullet::Init(wstring strKey, wstring fileName)
{
	m_imageBullet = make_shared<Image>();
	if (m_imageBullet)
	{
		m_imageBullet = GET_SINGLE(ImageManager)->AddImage(strKey, fileName);

		if (m_nWidth == 0)
			m_nWidth = m_imageBullet->GetWidth();
		if (m_nHeight == 0)
			m_nHeight = m_imageBullet->GetHeight();
	}
}

void Bullet::Update(float dt)
{
	m_fPosX += cosf(m_fAngle) * m_fSpeed * dt;
	m_fPosY += sinf(m_fAngle) * m_fSpeed * dt;
}


void Bullet::Render(HDC hdc)
{
	if (m_imageBullet)
		m_imageBullet->DrawBitmap(hdc, (int)m_fPosX, (int)m_fPosY, (int)(m_nWidth * m_fScale), (int)(m_nHeight * m_fScale));
}

void Bullet::Release()
{
	if (m_imageBullet)
		m_imageBullet->Release();
}

RECT Bullet::GetRect()
{
	RECT rt;
	rt.left = (LONG)(m_fPosX - m_nWidth * m_fScale / 2);
	rt.top = (LONG)(m_fPosY - m_nHeight * m_fScale / 2);
	rt.right = rt.left + (LONG)(m_nWidth * m_fScale);
	rt.bottom = rt.top + (LONG)(m_nHeight * m_fScale);
	return rt;
}

bool Bullet::IsValid()
{
	if ((int)(m_fPosY - m_nHeight * m_fScale / 2) > 0 && (int)(m_fPosY + m_nHeight * m_fScale / 2) < (int)g_Engine->GetHeight())
		return true;
	return false;
}

bool Bullet::IsCollision(RECT targetRect)
{
	RECT tempRT;
	RECT myRT = GetRect();
	if (IntersectRect(&tempRT, &myRT, &targetRect))
	{
		return true;
	}
	return false;
}
