#pragma once
#include "Scene.h"

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
	STAGE	m_stage;
};

