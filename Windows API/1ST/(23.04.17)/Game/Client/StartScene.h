#pragma once
#include "Scene.h"

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

public:
	void Init() override;
	void Update(float dt) override;
	void Render(HDC hdc) override;
	void Release() override;

private:
	float m_posX;
	float m_posY;
};

