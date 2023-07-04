#include "pch.h"
#include "Stage01_Scene.h"
#include "Camera.h"
#include "Player.h"
#include "PixelCollision.h"

Stage01_Scene::Stage01_Scene()
{
	m_camera = nullptr;
	m_player = nullptr;
	m_pixelCollision = nullptr;
	m_stage = STAGE::STAGE01;
}

Stage01_Scene::~Stage01_Scene()
{
}

void Stage01_Scene::Init()
{
	m_player = make_shared<Player>(100, 400);
	if (m_player)
		m_player->Init();

	m_pixelCollision = make_shared<PixelCollision>();
	if (m_pixelCollision)
	{
		m_pixelCollision->Init();
		m_pixelCollision->SetPlayer(m_player);
		m_pixelCollision->SetStage(m_stage);
	}

	m_camera = make_shared<Camera>();
	if (m_camera)
	{
		int width = g_Engine->GetWidth();
		int height = g_Engine->GetHeight();
		int backWidth = m_pixelCollision->GetImageWidth();
		int backHeight = m_pixelCollision->GetImageHeight();

		m_camera->Init(width, height, backWidth, backHeight);
		m_camera->SetPlayer(m_player);
	}

	//움직이는 이미지를 위한 카메라 세팅
	if (m_pixelCollision)
		m_pixelCollision->SetCamera(m_camera);

	SetStage(m_stage);
}

void Stage01_Scene::Update(float dt)
{
	if (m_player)
		m_player->Update(dt);

	if (m_pixelCollision)
		m_pixelCollision->Update(dt);
}

void Stage01_Scene::Render(HDC hdc)
{
	if (m_pixelCollision == nullptr)
		return;

	int backWidth = m_pixelCollision->GetImageWidth();
	int backHeight = m_pixelCollision->GetImageHeight();

	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = (HBITMAP)CreateCompatibleBitmap(hdc, backWidth, backHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	if (m_pixelCollision)
		m_pixelCollision->Render(hMemDC);

	if (m_player)
		m_player->Render(hMemDC);

	GdiTransparentBlt(hdc, 0, 0, g_Engine->GetWidth(), g_Engine->GetHeight(),
		hMemDC, m_camera->GetLeft(), m_camera->GetTop(), m_camera->GetWidth(), m_camera->GetHeight(), RGB(255, 0, 255));

	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}

void Stage01_Scene::Release()
{
	if (m_player)
		m_player->Release();

	if (m_pixelCollision)
		m_pixelCollision->Release();

	if (m_camera)
		m_camera->Release();
}

void Stage01_Scene::SetStage(STAGE stage)
{
	m_stage = stage;

	if (m_pixelCollision)
		m_pixelCollision->SetStage(stage);
}
