#pragma once
#include "Actor.h"

enum class LOOPIMAGE
{
	BG1,
	BG2,
	BG3,
	BG4,
	COUNT
};

typedef struct tagLOOPINFO
{
	shared_ptr<Image>	imgLoop = nullptr;
	int					posX = 0;
	int					speed = 100;
} LOOPINFO;

class Camera;
class Player;
class PixelCollision : public Actor
{
public:
	PixelCollision();
	virtual ~PixelCollision();

public:
	void	Init() override;
	void	Update(float dt) override;
	void	Render(HDC hdc) override;
	void	Release() override;

public:
	void	SetStage(STAGE stage);
	int		GetImageWidth() { return m_imgBG->GetWidth(); }
	int		GetImageHeight() { return m_imgBG->GetHeight(); }

public:
	void	SetPlayer(shared_ptr<Player> p) { m_player = p; }
	void	SetCamera(shared_ptr<Camera> c) { m_camera = c; }
	void	PlayerPixelCollision();

private:
	STAGE						m_stage;

	HDC							m_pixelDC;
	HBITMAP						m_oldBitmap;

	shared_ptr<Player>			m_player;
	shared_ptr<Camera>			m_camera;

	shared_ptr<Image>			m_imgBG;
	shared_ptr<Image>			m_imgPixel;
	vector<shared_ptr<Image>>	m_imgBGList;
	vector<shared_ptr<Image>>	m_imgPixelList;

	vector<LOOPINFO>			m_imgLoopList;
};

