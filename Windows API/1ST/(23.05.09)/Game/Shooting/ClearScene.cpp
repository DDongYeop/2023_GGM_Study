#include "pch.h"
#include "ClearScene.h"

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Init()
{
	m_imageBG = make_shared<Image>();
	if (m_imageBG)
	{
		m_imageBG = GET_SINGLE(ImageManager)->AddImage(L"IntroBG", L"Resources/UI/BG.bmp", false);
	}

	m_imageTitle = make_shared<Image>();
	if (m_imageTitle)
	{
		m_imageTitle = GET_SINGLE(ImageManager)->AddImage(L"WinTilte", L"Resources/UI/YouWin.bmp", true);
	}

	m_btnRePlay = make_shared<Image>();
	if (m_btnRePlay)
	{
		m_btnRePlay = GET_SINGLE(ImageManager)->AddImage(L"ReplayBTN", L"Resources/UI/Replay_BTN.bmp", true);
	}

	m_btnExit = make_shared<Image>();
	if (m_btnExit)
	{
		m_btnExit = GET_SINGLE(ImageManager)->AddImage(L"ExitBTN", L"Resources/UI/Exit_BTN.bmp", true);
	}
}

void ClearScene::Update(float dt)
{
	if (INPUT->GetButtonDown(KEY_TYPE::LBUTTON))
	{
		RECT replayRT = m_btnRePlay->GetBoundingBox();
		RECT eixtRT = m_btnExit->GetBoundingBox();
		POINT mousePos = INPUT->GetMousePos();

		if (PtInRect(&replayRT, mousePos))
			GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");

		if (PtInRect(&eixtRT, mousePos))
			PostQuitMessage(0);
	}
}

void ClearScene::Render(HDC hdc)
{
	int nWidth = g_Engine->GetWidth();
	int nHeight = g_Engine->GetHeight();
	if (m_imageBG)
		m_imageBG->DrawBitmap(hdc, 0, 0, nWidth, nHeight);

	if (m_imageTitle)
		m_imageTitle->DrawBitmap(hdc, nWidth / 2, nHeight / 5, 400, 50);

	if (m_btnRePlay)
		m_btnRePlay->DrawBitmap(hdc, nWidth / 2, nHeight - 170, 200, 60);

	if (m_btnExit)
		m_btnExit->DrawBitmap(hdc, nWidth / 2, nHeight - 100, 200, 60);
}

void ClearScene::Release()
{
	if (m_imageBG)
		m_imageBG->Release();

	if (m_imageTitle)
		m_imageTitle->Release();

	if (m_btnRePlay)
		m_btnRePlay->Release();

	if (m_btnExit)
		m_btnExit->Release();

	GET_SINGLE(ImageManager)->DeleteAll();
}
