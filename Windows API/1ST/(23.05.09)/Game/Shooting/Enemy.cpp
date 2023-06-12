#include "pch.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletManager.h"

Enemy::Enemy() : Pawn(0, 0)
{
	m_eEnemyType = ENEMY_TYPE::ENEMY_01;
	m_fMaxCreation = 3.0f;
	m_fCreationTime = 1.0f;
	m_fCurrentTime = 0.0f;
	m_fAngle = 90.0f * PI / 180.0f;
	m_ePawnType = PAWN_TYPE::ENEMY;
}

Enemy::Enemy(float x, float y, int width, int height, float scale, float speed, ENEMY_TYPE type) : Pawn(x, y, width, height, scale, speed)
{
	m_eEnemyType = type;
	m_fMaxCreation = 3.0f;
	m_fCreationTime = 1.0f;
	m_fCurrentTime = 0.0f;
	m_fAngle = 90.0f * PI / 180.0f;
	m_ePawnType = PAWN_TYPE::ENEMY;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_fCreationTime = rand() % (int)m_fMaxCreation + 1;

	m_imageEnemy = make_shared<Image>();
	if (m_imageEnemy)
	{
		switch (m_eEnemyType)
		{
		case ENEMY_TYPE::ENEMY_01:
			m_nScore = 1;
			m_imageEnemy = GET_SINGLE(ImageManager)->AddImage(L"Enemy01", L"Resources/Image/Enemy01.bmp");
			break;
		case ENEMY_TYPE::ENEMY_02:
			m_nScore = 3; 
			m_imageEnemy = GET_SINGLE(ImageManager)->AddImage(L"Enemy02", L"Resources/Image/Enemy02.bmp");
			break;
		case ENEMY_TYPE::ENEMY_03:
			m_nScore = 5; 
			m_imageEnemy = GET_SINGLE(ImageManager)->AddImage(L"Enemy03", L"Resources/Image/Enemy03.bmp");
			break;
		case ENEMY_TYPE::ENEMY_04:
			m_imageEnemy = GET_SINGLE(ImageManager)->AddImage(L"Enemy04", L"Resources/Image/Enemy04.bmp");
			break;
		case ENEMY_TYPE::BOSS:
			m_nScore = 100; 
			m_imageEnemy = GET_SINGLE(ImageManager)->AddImage(L"Boss", L"Resources/Image/Boss.bmp");
			break;
		default:
			break;
		}

		if (m_nWidth == 0)
			m_nWidth = m_imageEnemy->GetWidth();
		if (m_nHeight == 0)
			m_nHeight = m_imageEnemy->GetHeight();

		m_hpBar = make_shared<ProgressBar>();
		if (m_hpBar)
		{
			m_hpBar->Init(L"Resources/Image/bar_front_green.bmp", L"Resources/Image/bar_back.bmp", m_fPosX - (m_nWidth * m_fScale) / 2, m_fPosY + (m_nHeight * m_fScale) / 2, int(m_nWidth * m_fScale), 10);
		}
	}

	RECT rt;
	if (!g_Engine)
		return;

	GetClientRect(g_Engine->GetWndHandle(), &rt);
	m_fStartX = rt.left + m_nWidth;
	m_fEndX = rt.right - m_nWidth;
	m_fStartY = rt.top + m_nHeight;
	m_fEndY = rt.bottom / 3;
}

void Enemy::Update(float dt)
{
	m_fPosX += cosf(m_fAngle) * m_fSpeed * dt;
	m_fPosY += sinf(m_fAngle) * m_fSpeed * dt;

	// 몬스터의 이동 구간 제어 
	if (m_fPosX <= m_fStartX)
	{
		m_fPosX = m_fStartX;
		m_fSpeed = abs(m_fSpeed);
	}
	else if (m_fPosX >= m_fEndX)
	{
		m_fPosX = m_fEndX;
		m_fSpeed = -m_fSpeed;
	}
	else if (m_fPosY <= m_fStartY)
	{
		m_fPosY = m_fStartY;
		m_fSpeed = abs(m_fSpeed);
	}
	else if (m_fPosY >= m_fEndY)
	{
		m_fPosY = m_fEndY;
		m_fSpeed = -m_fSpeed;
	}

	m_fCurrentTime += dt;
	if (m_fCurrentTime > m_fCreationTime)
	{
		CreateBullet();

		m_fCreationTime = rand() % (int)m_fMaxCreation + 1;
		m_fCurrentTime = 0.0f;
	}

	if (m_hpBar)
	{
		m_hpBar->SetGauge(m_fHP, m_fMaxHP);
		m_hpBar->SetPosition(m_fPosX - (m_nWidth * m_fScale) / 2, m_fPosY + (m_nHeight * m_fScale) / 2);
	}
}

void Enemy::Render(HDC hdc)
{
	if (m_imageEnemy)
		m_imageEnemy->DrawBitmap(hdc, (int)m_fPosX, (int)m_fPosY, (int)(m_nWidth * m_fScale), (int)(m_nHeight * m_fScale));

	if (m_hpBar)
		m_hpBar->Render(hdc);
}

void Enemy::Release()
{
	if (m_imageEnemy)
		m_imageEnemy->Release();

	if (m_hpBar)
		m_hpBar->Release();
}

void Enemy::OnDamageProcess(float damage)
{
	Pawn::OnDamageProcess(damage);

	GET_SINGLE(SoundManager)->Play(L"hit", 0.5f);
}

void Enemy::CreateBullet()
{
	if (m_eEnemyType == ENEMY_TYPE::ENEMY_01)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>(m_fPosX, m_fPosY);
		if (bullet)
		{
			bullet->SetAngle(90.0f * PI / 180.0f);
			bullet->SetOwnerPawn(weak_from_this());
			bullet->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet);
		}
	}
	else if (m_eEnemyType == ENEMY_TYPE::ENEMY_02)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>(m_fPosX, m_fPosY);
		if (bullet)
		{
			bullet->SetAngle(90.0f * PI / 180.0f);
			bullet->SetOwnerPawn(weak_from_this());
			bullet->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet);
		}
		shared_ptr<Bullet> bullet2 = make_shared<Bullet>(m_fPosX, m_fPosY + m_nHeight);
		if (bullet2)
		{
			bullet2->SetAngle(90.0f * PI / 180.0f);
			bullet2->SetOwnerPawn(weak_from_this());
			bullet2->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet2->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet2);
		}
	}
	else if (m_eEnemyType == ENEMY_TYPE::ENEMY_03)
	{
		auto player = m_player.lock();

		shared_ptr<Bullet> bullet3 = make_shared<Bullet>(m_fPosX, m_fPosY);
		if (bullet3)
		{
			float angle = getAngle(m_fPosX, -m_fPosY, player->GetPosX(), -player->GetPosY());
			bullet3->SetAngle(angle);
			bullet3->SetOwnerPawn(weak_from_this());
			bullet3->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet3->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet3);
		}
	}
	else if (m_eEnemyType == ENEMY_TYPE::ENEMY_04)
	{
		shared_ptr<Bullet> bullet4 = make_shared<Bullet>(m_fPosX, m_fPosY);
		if (bullet4)
		{
			bullet4->SetAngle(90.0f * PI / 180.0f);
			bullet4->SetOwnerPawn(weak_from_this());
			bullet4->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet4->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet4);
		}
		shared_ptr<Bullet> bullet5 = make_shared<Bullet>(m_fPosX, m_fPosY);
		if (bullet5)
		{
			bullet5->SetAngle(105.0f * PI / 180.0f);
			bullet5->SetOwnerPawn(weak_from_this());
			bullet5->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet5->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet5);
		}
		shared_ptr<Bullet> bullet6 = make_shared<Bullet>(m_fPosX, m_fPosY);
		if (bullet6)
		{
			bullet6->SetAngle(75.0f * PI / 180.0f);
			bullet6->SetOwnerPawn(weak_from_this());
			bullet6->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
			bullet6->SetDamage(m_fDamage);
			GET_SINGLE(BulletManager)->CreateBullet(bullet6);
		}
	}
	else if (m_eEnemyType == ENEMY_TYPE::BOSS)
	{
		int nRandom = rand() % 3;
		if (nRandom == 0)
		{
			for (int i = 0; i < 10; ++i)
			{
				shared_ptr<Bullet> bullet = make_shared<Bullet>(m_fPosX, m_fPosY);
				if (bullet)
				{
					bullet->SetAngle(2 * PI / 10 * i);
					bullet->SetOwnerPawn(weak_from_this());
					bullet->Init(L"projectile05_3", L"Resources/Image/projectile05_3.bmp");
					bullet->SetDamage(m_fDamage);
					GET_SINGLE(BulletManager)->CreateBullet(bullet);
				}
			}
		}
		else if (nRandom == 1)
		{
			for (int i = 0; i < 10; ++i)
			{
				shared_ptr<Bullet> bullet = make_shared<Bullet>(m_fPosX, m_fPosY);
				if (bullet)
				{
					bullet->SetAngle(PI / 10 * i);
					bullet->SetOwnerPawn(weak_from_this());
					bullet->Init(L"projectile03_3", L"Resources/Image/projectile03_3.bmp");
					bullet->SetDamage(m_fDamage);
					GET_SINGLE(BulletManager)->CreateBullet(bullet);
				}
			}
		}
		else
		{
			auto player = m_player.lock();
			
			for (int i = 0; i < 3; ++i)
			{
				shared_ptr<Bullet> bullet3 = make_shared<Bullet>(m_fPosX, m_fPosY + m_nHeight * i);
				if (bullet3)
				{
					float angle = getAngle(m_fPosX, -m_fPosY, player->GetPosX(), -player->GetPosY());
					bullet3->SetAngle(angle);
					bullet3->SetOwnerPawn(weak_from_this());
					bullet3->Init(L"projectile04_3", L"Resources/Image/projectile04_3.bmp");
					bullet3->SetDamage(m_fDamage);
					GET_SINGLE(BulletManager)->CreateBullet(bullet3);
				}
			}
		}
	}
}
