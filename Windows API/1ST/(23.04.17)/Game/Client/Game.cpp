#include "pch.h"
#include "Game.h"
#include "StartScene.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	GET_SINGLE(SceneManager)->RegisterScene(_T("StartScene"), make_shared<StartScene>());
	GET_SINGLE(SceneManager)->LoadScene(_T("StartScene"));
}

void Game::Update(float dt)
{	
}

void Game::Render(HDC hdc)
{
}

void Game::Release()
{
}
