#include "pch.h"
#include "StartWindow.h"
#include "Stage01_Scene.h"

StartWindow::StartWindow()
{
}

StartWindow::~StartWindow()
{
}

void StartWindow::Init()
{
	GET_SINGLE(SceneManager)->RegisterScene(L"Stage01", make_shared<Stage01_Scene>());

	GET_SINGLE(SceneManager)->LoadScene(L"Stage01");
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
