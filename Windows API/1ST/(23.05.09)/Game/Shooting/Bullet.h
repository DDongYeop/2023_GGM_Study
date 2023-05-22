#pragma once
#include "Actor.h"

class Pawn;
class Bullet : public Actor
{
public:
	Bullet();
	Bullet(float x, float y, int width = 0, int height = 0, float scale = 1.0f, float speed = 200.0f, float angle = -90.0f * PI / 180.0f);
	virtual ~Bullet();

public:
	void	Init() override;
	void	Init(wstring strKey, wstring fileName);
	void	Update(float dt) override;
	void	Render(HDC hdc) override;
	void	Release() override;

public:
	RECT	GetRect();
	bool	IsValid();
	bool	IsCollision(RECT targetRect);

public:
	void	SetSpeed(float speed) { m_fSpeed = speed; }
	float	GetSpeed() { return m_fSpeed; }
	void	SetAngle(float angle) { m_fAngle = angle; }
	float	GetAngle() { return m_fAngle; }

	void	SetOwnerPawn(weak_ptr<Pawn> owner) { m_ownerPawn = owner; }
	weak_ptr<Pawn> GetOwnerPawn() { return m_ownerPawn; }

private:
	float				m_fSpeed;
	float				m_fAngle;
	
	weak_ptr<Pawn>		m_ownerPawn;
	shared_ptr<Image>	m_imageBullet;
};

