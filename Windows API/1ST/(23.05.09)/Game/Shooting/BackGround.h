#pragma once
#include "Actor.h"

class BackGround : public Actor
{
public:
	BackGround();
	BackGround(float x, float y, int width = 0, int height = 0, float scale = 1.0f, float scrollY = 0.0f, float scrollSpeed = 100.0f);
	virtual ~BackGround();

public:
	void	Init() override;
	void	Update(float dt) override;
	void	Render(HDC hdc) override;
	void	Release() override;

private:
	shared_ptr<Image>		m_imageBG;
	RECT					m_rcDraw;
	float					m_fScrollY;
	float					m_fScrollSpeed;
};

