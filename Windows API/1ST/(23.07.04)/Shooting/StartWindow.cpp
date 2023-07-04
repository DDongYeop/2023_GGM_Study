#include "pch.h"
#include "StartWindow.h"
#include "GameScene.h"
#include "IntroScene.h"

StartWindow::StartWindow()
{
}

StartWindow::~StartWindow()
{
}

void StartWindow::Init()
{
	// ¾À ¹Ì¸® µî·Ï
	GET_SINGLE(SceneManager)->RegisterScene(L"IntroScene", make_shared<IntroScene>());
	GET_SINGLE(SceneManager)->RegisterScene(L"GameScene", make_shared<GameScene>());

	// ÇöÀç ¾À ·Îµå
	GET_SINGLE(SceneManager)->LoadScene(L"IntroScene");
}

void StartWindow::Update(float dt)
{
}

void StartWindow::Render(HDC hdc)
{
}

void StartWindow::Release()
{
}
