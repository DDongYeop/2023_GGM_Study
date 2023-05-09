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
	m_offsetY = 0;
	m_offsetSpeed = 200;

	GET_SINGLE(SoundManager)->AddSound(_T("Attack"), _T("../Resources/Sound/Character_attack.wav"));
	GET_SINGLE(SoundManager)->AddSound(_T("BGM"), _T("../Resources/Sound/Thinking Out Loud.WAV"), true, true);
	GET_SINGLE(SoundManager)->AddSound(_T("Linda"), _T("../Resources/Sound/Linda.mp3"), true, true);

	GET_SINGLE(SoundManager)->Play(_T("BGM"), 0.5f);

	m_player = GET_SINGLE(ImageManager)->AddImage(L"Player", L"../Resources/Image/Pikachu.bmp");
	m_map = GET_SINGLE(ImageManager)->AddImage(L"BgImage", L"../Resources/Image/bgImage.bmp");
	m_map->SetCenter(FALSE);
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

	m_offsetY -= m_offsetSpeed * dt;
}

void StartScene::Render(HDC hdc)
{
	RECT rtDraw = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if( m_map )
		m_map->DrawLoopBitmap(hdc, &rtDraw, 0, m_offsetY);

	if (m_player)
	{
		m_player->DrawBitmap(hdc, 200, 100, 200, 200);
		RECT rc = m_player->GetBoundingBox();
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		m_player->DrawBitmap(hdc, 200, 250);
		rc = m_player->GetBoundingBox();
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		m_player->DrawAlpha(hdc, 400, 300, 100, 200, 200);
		rc = m_player->GetBoundingBox();
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		m_player->DrawAlpha(hdc, 400, 450, 150);
		rc = m_player->GetBoundingBox();
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		m_player->DrawRotate(hdc, 600, 300, 90, 200, 200);
		rc = m_player->GetBoundingBox();
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom); 
		
		m_player->DrawRotate(hdc, 600, 450, 45);
		rc = m_player->GetBoundingBox();
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}

}

void StartScene::Release()
{
}
