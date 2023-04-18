#include "pch.h"
#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Init()
{
	m_posX = 100.0f;
	m_posY = 100.0f;
}

void StartScene::Update(float dt)
{
	if (INPUT->GetButton(KEY_TYPE::UP))
		m_posY -= 100.0f * dt;
	if (INPUT->GetButton(KEY_TYPE::DOWN))
		m_posY += 100.0f * dt;
	if (INPUT->GetButton(KEY_TYPE::RIGHT))
		m_posX += 100.0f * dt;
	if (INPUT->GetButton(KEY_TYPE::LEFT))
		m_posX -= 100.0f * dt;
}

void StartScene::Render(HDC hdc)
{
	Rectangle(hdc, m_posX, m_posY, m_posX + 100, m_posY + 100);
}

void StartScene::Release()
{
}
