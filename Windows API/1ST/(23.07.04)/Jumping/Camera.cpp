#include "pch.h"
#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	m_width = 0;
	m_height = 0;
	m_backWidth = 0;
	m_backHeight = 0;

	m_player = nullptr;
}

Camera::~Camera()
{
	m_player = nullptr;
}

void Camera::Init(int width, int height, int backWidth, int backHeight)
{
	m_width = width;
	m_height = height;
	m_backWidth = backWidth;
	m_backHeight = backHeight;
}

void Camera::Release()
{
	m_player = nullptr;
}

bool Camera::CheckCameraX()
{
	if (m_player == nullptr)
		return false;

	if (m_player->GetPosX() - m_width / 2 <= 0 ||
		m_player->GetPosX() + m_width / 2 >= m_backWidth)
		return false;

	return true;
}

bool Camera::CheckCameraY()
{
	if (m_player == nullptr)
		return false;

	if (m_player->GetPosY() - m_height / 2 <= 0 ||
		m_player->GetPosY() + m_height / 2 >= m_backHeight)
		return false;

	return true;
}

int Camera::GetLeft()
{
	if (CheckCameraX() == false)
	{
		if (m_player->GetPosX() <= m_width / 2)
			return 0;
		return m_backWidth - m_width;
	}

	return (int)m_player->GetPosX() - m_width / 2;
}

int Camera::GetTop()
{
	if (CheckCameraY() == false)
	{
		if (m_player->GetPosY() <= m_height / 2)
			return 0;
		return m_backHeight - m_height;
	}

	return (int)m_player->GetPosY() - m_height / 2;
}
