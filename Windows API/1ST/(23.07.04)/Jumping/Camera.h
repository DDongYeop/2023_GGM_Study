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
	int					m_width;		// ī�޶� ���� ũ��
	int					m_height;		// ī�޶� ���� ũ��
	int					m_backWidth;	// ��� �̹��� ����ũ��
	int					m_backHeight;	// ��� �̹��� ����ũ��
	shared_ptr<Player>	m_player;
};

