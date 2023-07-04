#pragma once

class Pawn;
class Enemy;
class EnemyManager
{
	DECLARE_SINGLE(EnemyManager);

public:
	void	Init(weak_ptr<Pawn> player, GAME_STAGE stage = GAME_STAGE::STAGE_01);
	void	Update(float dt);
	void	Render(HDC hdc);
	void	Release();

public:
	void	CreateEnemy(GAME_STAGE stage);

public:
	void						SetPlayer(weak_ptr<Pawn> player) { m_player = player; }
	weak_ptr<Pawn>				GetPlayer() { return m_player; }

	list<shared_ptr<Enemy>>&	GetEnemies() { return m_Enemies; }

private:
	GAME_STAGE				m_eStage;
	weak_ptr<Pawn>			m_player;
	list<shared_ptr<Enemy>>	m_Enemies;
};

