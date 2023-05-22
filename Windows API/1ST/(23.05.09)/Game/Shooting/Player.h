#pragma once
#include "Pawn.h"

class Player : public Pawn, public enable_shared_from_this<Player>
{
public:
	Player();
	Player(float x, float y, int width = 0, int height = 0, float scale = 1.0f, float speed = 100.0f);
	virtual ~Player();

public:
	void	Init() override;
	void	Update(float dt) override;
	void	Render(HDC hdc) override;
	void	Release() override;

public:
	void	CreateBullet();

private:
	int						m_nLevel;
	shared_ptr<Image>		m_imagePlayer;
	shared_ptr<ProgressBar>	m_hpBar;
};

