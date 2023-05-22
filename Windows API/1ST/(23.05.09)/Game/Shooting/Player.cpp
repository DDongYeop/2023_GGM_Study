#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"

Player::Player() : Pawn(0, 0)
{
	m_nLevel = 1;
}

Player::Player(float x, float y, int width, int height, float scale, float speed) : Pawn(x, y, width, height, scale, speed)
{
	m_nLevel = 1;
}

Player::~Player()
{
}

void Player::Init()
{
	m_imagePlayer = make_shared<Image>();
	if (m_imagePlayer)
	{
		m_imagePlayer = GET_SINGLE(ImageManager)->AddImage(L"Player", L"Resources/Image/Spaceship.bmp");

		if (m_nWidth == 0)
			m_nWidth = m_imagePlayer->GetWidth();
		if (m_nHeight == 0)
			m_nHeight = m_imagePlayer->GetHeight();
	}

	m_hpBar = make_shared<ProgressBar>();
	if (m_hpBar)
	{
		m_hpBar->Init(L"Resources/Image/bar_front_red.bmp", L"Resources/Image/bar_back.bmp", m_fPosX - (m_nWidth * m_fScale) / 2, m_fPosY + (m_nHeight * m_fScale) / 2, int(m_nWidth * m_fScale), 10);
	}
}

void Player::Update(float dt)
{
	if (INPUT->GetButton(KEY_TYPE::UP))
		m_fPosY -= m_fSpeed * dt;
	if (INPUT->GetButton(KEY_TYPE::DOWN))
		m_fPosY += m_fSpeed * dt;
	if (INPUT->GetButton(KEY_TYPE::LEFT))
		m_fPosX -= m_fSpeed * dt;
	if (INPUT->GetButton(KEY_TYPE::RIGHT))
		m_fPosX += m_fSpeed * dt;

	if (INPUT->GetButtonDown(KEY_TYPE::SPACE))
		CreateBullet();

	if (m_hpBar)
	{
		m_hpBar->SetGauge(m_fHP, m_fMaxHP);
		m_hpBar->SetPosition(m_fPosX - m_nWidth * m_fScale / 2, m_fPosY + m_nHeight * m_fScale / 2);
	}
}

void Player::Render(HDC hdc)
{
	if (m_imagePlayer)
		m_imagePlayer->DrawBitmap(hdc, (int)m_fPosX, (int)m_fPosY, int(m_nWidth * m_fScale), int(m_nHeight * m_fScale));

	if (m_hpBar)
		m_hpBar->Render(hdc);
}

void Player::Release()
{
	if (m_imagePlayer)
		m_imagePlayer->Release();

	if (m_hpBar)
		m_hpBar->Release();
}

void Player::CreateBullet()
{
	if (m_nLevel == 1)
	{
		float posX = m_fPosX;
		float posY = m_fPosY - m_nHeight * m_fScale / 2;
		shared_ptr<Bullet> bullet = make_shared<Bullet>(posX, posY);
		if (bullet)
		{
			bullet->SetOwnerPawn(weak_from_this());
			bullet->Init();
			GET_SINGLE(BulletManager)->CreateBullet(bullet);
		}
	}
}
