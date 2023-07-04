#pragma once

class Player;
class Camera
{
public:
	Camera();
	~Camera();

public:
	void Init(int width, int height, int backWidth, int backHeight);
	void Release();

public:
	void	SetPlayer(shared_ptr<Player> p) { m_player = p; }

	bool	CheckCameraX();
	bool	CheckCameraY();

	int		GetLeft();
	int		GetTop();
	int		GetWidth() { return m_width; }
	int		GetHeight() { return m_height; }

private:
	int					m_width;		// 카메라 가로 크기
	int					m_height;		// 카메라 세로 크기
	int					m_backWidth;	// 배경 이미지 가로크기
	int					m_backHeight;	// 배경 이미지 세로크기
	shared_ptr<Player>	m_player;
};

