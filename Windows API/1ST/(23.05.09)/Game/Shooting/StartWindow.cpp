#include "pch.h"
#include "StartWindow.h"
#include "GameScene.h"
#include "IntroScene.h"
#include "ClearScene.h"
#include "LoseScene.h"

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
	GET_SINGLE(SceneManager)->RegisterScene(L"ClearScene", make_shared<ClearScene>());
	GET_SINGLE(SceneManager)->RegisterScene(L"LoseScene", make_shared<LoseScene>());
	
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
