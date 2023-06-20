#include "pch.h"
#include "Stage01_Scene.h"

Stage01_Scene::Stage01_Scene()
{
	m_stage = STAGE::STAGE01;
}

Stage01_Scene::~Stage01_Scene()
{
}

void Stage01_Scene::Init()
{
	SetStage(STAGE::STAGE01);
}

void Stage01_Scene::Update(float dt)
{
}

void Stage01_Scene::Render(HDC hdc)
{
}

void Stage01_Scene::Release()
{
}

void Stage01_Scene::SetStage(STAGE stage)
{
	m_stage = stage;
}
