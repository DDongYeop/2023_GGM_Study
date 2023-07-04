#pragma once

class Pawn;
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
	void	AddPawn(weak_ptr<Pawn> pawn);
	void	DeletePawn(weak_ptr<Pawn> pawn);

private:
	list<shared_ptr<Bullet>>	m_Bullets;
	list<weak_ptr<Pawn>>		m_Pawns;
};

