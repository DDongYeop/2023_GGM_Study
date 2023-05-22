#include "pch.h"
#include "BulletManager.h"
#include "Bullet.h"

void BulletManager::Init()
{
	m_Bullets.clear();
}

void BulletManager::Update(float dt)
{
	list<shared_ptr<Bullet>>::iterator iter = m_Bullets.begin();
	while (iter != m_Bullets.end())
	{
		(*iter)->Update(dt);

		if ((*iter)->IsValid() == false)
		{
			iter = m_Bullets.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void BulletManager::Render(HDC hdc)
{
	list<shared_ptr<Bullet>>::iterator iter;
	for (iter = m_Bullets.begin(); iter != m_Bullets.end(); ++iter)
	{
		(*iter)->Render(hdc);
	}
}

void BulletManager::Release()
{
	list<shared_ptr<Bullet>>::iterator iter;
	for (iter = m_Bullets.begin(); iter != m_Bullets.end(); ++iter)
	{
		(*iter)->Release();
	}
	m_Bullets.clear();
}

void BulletManager::CreateBullet(shared_ptr<Bullet> bullet)
{
	if (bullet)
	{
		m_Bullets.push_back(bullet);
	}
}
