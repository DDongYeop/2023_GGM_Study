#pragma once
#include "Actor.h"

class Pawn : public Actor
{
public:
	Pawn();
	Pawn(float x, float y, int width = 0, int height = 0, float scale = 1.0f, float speed = 100.0f);
	virtual ~Pawn();

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	RECT	GetRect();

	void	SetSpeed(float speed)	{ m_fSpeed = speed;		}
	float	GetSpeed()				{ return m_fSpeed;		}
	void	SetHP(float hp)			{ m_fHP = hp;			}
	float	GetHP()					{ return m_fHP;			}
	void	SetMaxHP(float hp)		{ m_fMaxHP = hp;		}
	float	GetMaxHP()				{ return m_fMaxHP;		}
	void	AddHP(float hp)			{ m_fHP += hp;			}
	void	SetDamage(float damage)	{ m_fDamage = damage;	}
	float	GetDamage()				{ return m_fDamage;		}

protected:
	float	m_fSpeed;
	float	m_fHP;
	float	m_fMaxHP;
	float	m_fDamage;
};

