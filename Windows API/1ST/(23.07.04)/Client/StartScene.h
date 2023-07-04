#pragma once
#include "Scene.h"

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

public:
	void Init()override;
	void Update(float dt)override;
	void Render(HDC hdc)override;
	void Release()override;

private:
	float	m_posX;
	float	m_posY;
	
	int		m_offsetY;
	int		m_offsetSpeed;

	shared_ptr<Image> m_player;
	shared_ptr<Image> m_map;

	shared_ptr<ProgressBar> m_progressBar;
};

