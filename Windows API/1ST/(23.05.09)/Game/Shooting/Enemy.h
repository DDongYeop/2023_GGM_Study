#pragma once
#include "Pawn.h"

class Enemy : public Pawn, public enable_shared_from_this<Enemy>
{
public:
	Enemy();
	Enemy(float x, float y, int width = 0, int height = 0, float scale = 1.0f, float speed = 100.0f, ENEMY_TYPE type = ENEMY_TYPE::ENEMY_01);
	virtual ~Enemy();

public:
	void	Init();
	void	Update(float dt);
	void	Render(HDC hdc);
	void	Release();

public:
	void	CreateBullet();

public:
	void			SetAngle(float angle) { m_fAngle = angle; }
	float			GetAngle() { return m_fAngle; }

	void			SetMaxCreation(float time) { m_fMaxCreation = time; }
	float			GetMaxCreation() { return m_fMaxCreation; }

	void			SetEnemyType(ENEMY_TYPE type) { m_eEnemyType = type; }
	ENEMY_TYPE		GetEnemyType() { return m_eEnemyType; }

	void			SetPlayer(weak_ptr<Pawn> player) { m_player = player; }
	weak_ptr<Pawn>	GetPlayer() { return m_player; }

private:
	float						m_fAngle;
	float						m_fMaxCreation;
	float						m_fCreationTime;
	float						m_fCurrentTime;
	ENEMY_TYPE					m_eEnemyType;

	weak_ptr<Pawn>				m_player;
	shared_ptr<Image>			m_imageEnemy;
	shared_ptr<ProgressBar>		m_hpBar;
};
