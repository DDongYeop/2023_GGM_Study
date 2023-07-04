#pragma once
#include "Scene.h"

class Camera;
class Player;
class PixelCollision;
class Stage01_Scene : public Scene
{
public:
	Stage01_Scene();
	virtual ~Stage01_Scene();

public:
	void	Init() override;
	void	Update(float dt) override;
	void	Render(HDC hdc) override;
	void	Release() override;

public:
	void	SetStage(STAGE stage);

private:
	STAGE						m_stage;

	shared_ptr<Camera>			m_camera;
	shared_ptr<Player>			m_player;
	shared_ptr<PixelCollision>	m_pixelCollision;
};

