#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

public:
	void Init() override;
	void Update(float dt) override;
	void Render(HDC hdc) override;
	void Release() override;
};

