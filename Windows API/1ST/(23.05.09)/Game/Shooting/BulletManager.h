#pragma once

class Bullet;
class BulletManager
{
	DECLARE_SINGLE(BulletManager);

public:
	void	Init();
	void	Update(float dt);
	void	Render(HDC hdc);
	void	Release();

public:
	void	CreateBullet(shared_ptr<Bullet> bullet);

private:
	list<shared_ptr<Bullet>>	m_Bullets;
};
