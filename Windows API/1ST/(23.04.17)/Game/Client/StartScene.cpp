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

	GET_SINGLE(SoundManager)->AddSound(_T("Attack"), _T("../Resources/Sound/Character_attack.wav"));
	GET_SINGLE(SoundManager)->AddSound(_T("BGM"), _T("../Resources/Sound/Thinking Out Loud.WAV"), true, true);
	GET_SINGLE(SoundManager)->AddSound(_T("Linda"), _T("../Resources/Sound/Linda.mp3"), true, true);

	GET_SINGLE(SoundManager)->Play(_T("BGM"), 0.5f);
}

void StartScene::Update(float dt)
{
	if (INPUT->GetButton(KEY_TYPE::UP))
		m_posY -= 100.0f * dt;
	if (INPUT->GetButton(KEY_TYPE::DOWN))
		m_posY += 100.0f * dt;
	if (INPUT->GetButton(KEY_TYPE::RIGHT))
		m_posX += 100.0f * dt;
	if (INPUT->GetButton(KEY_TYPE::SPACE))
		GET_SINGLE(SoundManager)->Play(_T("Attack"), 0.5f);
}

void StartScene::Render(HDC hdc)
{
	Rectangle(hdc, m_posX, m_posY, m_posX + 100, m_posY + 100);
}

void StartScene::Release()
{
}
