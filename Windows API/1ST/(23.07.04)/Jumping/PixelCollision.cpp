#include "pch.h"
#include "PixelCollision.h"
#include "Player.h"
#include "Camera.h"

PixelCollision::PixelCollision()
{
	m_pixelDC = nullptr;
	m_player = nullptr;
	m_camera = nullptr;

	m_imgBG = nullptr;
	m_imgPixel = nullptr;
	m_stage = STAGE::STAGE02;
}

PixelCollision::~PixelCollision()
{
	if (m_pixelDC)
	{
		SelectObject(m_pixelDC, m_oldBitmap);
		DeleteDC(m_pixelDC);
	}

	m_imgBG = nullptr;
	m_imgPixel = nullptr;
}

void PixelCollision::Init()
{
	m_imgBGList.resize((UINT)STAGE::COUNT);
	m_imgBGList[(UINT)STAGE::STAGE01] = GET_SINGLE(ImageManager)->AddImage(L"BG01", L"Resources/BG/background1.bmp", false);
	m_imgBGList[(UINT)STAGE::STAGE02] = GET_SINGLE(ImageManager)->AddImage(L"BG02", L"Resources/BG/background2.bmp", false);
	m_imgBGList[(UINT)STAGE::STAGE03] = GET_SINGLE(ImageManager)->AddImage(L"BG03", L"Resources/BG/background3.bmp", false);
	m_imgBGList[(UINT)STAGE::STAGE04] = GET_SINGLE(ImageManager)->AddImage(L"BG04", L"Resources/BG/background4.bmp", false);

	m_imgPixelList.resize((UINT)STAGE::COUNT);
	m_imgPixelList[(UINT)STAGE::STAGE01] = GET_SINGLE(ImageManager)->AddImage(L"PIXEL01", L"Resources/BG/background1_pixel.bmp", false);
	m_imgPixelList[(UINT)STAGE::STAGE02] = GET_SINGLE(ImageManager)->AddImage(L"PIXEL02", L"Resources/BG/background2_pixel.bmp", false);
	m_imgPixelList[(UINT)STAGE::STAGE03] = GET_SINGLE(ImageManager)->AddImage(L"PIXEL03", L"Resources/BG/background3_pixel.bmp", false);
	m_imgPixelList[(UINT)STAGE::STAGE04] = GET_SINGLE(ImageManager)->AddImage(L"PIXEL04", L"Resources/BG/background4_pixel.bmp", false);

	//움직이는 배경 이미지 로드
	m_imgLoopList.resize((UINT)LOOPIMAGE::COUNT);
	m_imgLoopList[(UINT)LOOPIMAGE::BG1].imgLoop = GET_SINGLE(ImageManager)->AddImage(L"LOOP01", L"Resources/BG/back1.bmp", false);
	m_imgLoopList[(UINT)LOOPIMAGE::BG1].speed = 100;
	m_imgLoopList[(UINT)LOOPIMAGE::BG2].imgLoop = GET_SINGLE(ImageManager)->AddImage(L"LOOP02", L"Resources/BG/back2.bmp", false);
	m_imgLoopList[(UINT)LOOPIMAGE::BG2].speed = 50;
	m_imgLoopList[(UINT)LOOPIMAGE::BG3].imgLoop = GET_SINGLE(ImageManager)->AddImage(L"LOOP03", L"Resources/BG/back3.bmp", false);
	m_imgLoopList[(UINT)LOOPIMAGE::BG3].speed = 0;
	m_imgLoopList[(UINT)LOOPIMAGE::BG4].imgLoop = GET_SINGLE(ImageManager)->AddImage(L"LOOP04", L"Resources/BG/back4.bmp", false);
	m_imgLoopList[(UINT)LOOPIMAGE::BG4].speed = 50;
}

void PixelCollision::Update(float dt)
{
	PlayerPixelCollision();

	if (m_player == nullptr || m_camera == nullptr)
		return;
	if (m_camera->CheckCameraX())
	{
		for (auto iter = m_imgLoopList.begin(); iter != m_imgLoopList.end(); ++iter)
		{
			if (m_player->IsMovingRight())
				(iter)->posX += (iter)->speed * dt;
			else if (m_player->IsMovingLeft())
				(iter)->posX -= (iter)->speed * dt;
			
		}
	}
}

void PixelCollision::Render(HDC hdc)
{
	// 움직이는 배경 
	int width = g_Engine->GetWidth();
	int height = g_Engine->GetHeight();

	RECT rt = { 0, 0, width * 2, height };

	for (auto iter = m_imgLoopList.rbegin(); iter != m_imgLoopList.rend(); ++iter)
	{
		(iter)->imgLoop->DrawLoopBitmap(hdc, &rt, (iter)->posX, 0);
	}

	// 실제 맵 배경
	if (m_imgBG)
		m_imgBG->DrawBitmap(hdc, 0, 0);
}

void PixelCollision::Release()
{
	m_imgBG = nullptr;
	for (int i = 0; i < m_imgBGList.size(); ++i)
	{
		m_imgBGList[i]->Release();
		m_imgBGList[i] = nullptr;
	}

	m_imgPixel = nullptr;
	for (int i = 0; i < m_imgPixelList.size(); ++i)
	{
		m_imgPixelList[i]->Release();
		m_imgPixelList[i] = nullptr;
	}

	for (auto iter = m_imgLoopList.begin(); iter != m_imgLoopList.end(); ++iter)
	{
		iter->imgLoop->Release();
		iter->imgLoop = nullptr;
	}
}

void PixelCollision::SetStage(STAGE stage)
{
	if ((UINT)stage < 0 || (UINT)stage >= (UINT)STAGE::COUNT)
		return;

	m_stage = stage;

	m_imgBG = m_imgBGList[(UINT)stage];
	m_imgPixel = m_imgPixelList[(UINT)stage];

	if (m_pixelDC)
	{
		SelectObject(m_pixelDC, m_oldBitmap);
		DeleteDC(m_pixelDC);
	}

	HDC hdc = GetDC(g_Engine->GetWndHandle());
	m_pixelDC = CreateCompatibleDC(hdc);

	m_oldBitmap = (HBITMAP)SelectObject(m_pixelDC, m_imgPixel->GetBitmapHandle());
}

void PixelCollision::PlayerPixelCollision()
{
	if (m_player == nullptr)
		return;

	for (int y = m_player->GetPosY(); y <= m_player->GetPosY() + m_player->GetHeight() / 2; ++y)
	{
		for (int x = m_player->GetPosX() - m_player->GetWidth() / 2; x <= m_player->GetPosX() + m_player->GetWidth() / 2; ++x)
		{
			COLORREF color = GetPixel(m_pixelDC, x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				if (m_player->IsOnGround() == false)
				{
					m_player->SetGround(true);
					break;
				}
			}
			else
			{
				m_player->SetGround(false);
			}
		}
	}

	for (int y = m_player->GetPosY() - m_player->GetHeight() / 2; y <= m_player->GetPosY() + m_player->GetHeight() / 3; ++y)
	{
		int x;
		if (m_player->IsRight())
			x = m_player->GetPosX() + m_player->GetWidth() / 2;
		else
			x = m_player->GetPosX() - m_player->GetWidth() / 2;

		COLORREF color = GetPixel(m_pixelDC, x, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			if (m_player->IsRight())
				m_player->SetCanMoveRight(false);
			else
				m_player->SetCanMoveLeft(false);
			break;
		}
		else if (r == 255 && g == 0 && b == 255)
		{
			// 다음 스테이지
			m_player->SetPos(400, 200);
			SetStage(static_cast<STAGE>(static_cast<int>(m_stage) + 1));
			break;
		}
		else
		{
			m_player->SetCanMoveRight(true);
			m_player->SetCanMoveLeft(true);
		}
	}
}
