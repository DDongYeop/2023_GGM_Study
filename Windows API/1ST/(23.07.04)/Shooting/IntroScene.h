#pragma once
#include "Scene.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	virtual ~IntroScene();

public:
	void Init() override;
	void Update(float dt)override;
	void Render(HDC hdc)override;
	void Release()override;

private:
	shared_ptr<Image>	m_imageBG;
	shared_ptr<Image>	m_imageTitle;
	shared_ptr<Image>	m_imageShip;
	shared_ptr<Image>	m_btnPlay;
	shared_ptr<Image>	m_btnExit;
};

