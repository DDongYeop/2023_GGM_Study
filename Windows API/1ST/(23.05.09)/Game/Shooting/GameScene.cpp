#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	srand((unsigned int)time(nullptr));

	m_player = make_shared<Player>(250, 600, 0, 0, 1.0f, 200.0f);
	if (m_player)
	{
		m_player->Init();
	}

	GET_SINGLE(EnemyManager)->Init(m_player, GAME_STAGE::STAGE_01);

	GET_SINGLE(BulletManager)->Init();
}

void GameScene::Update(float dt)
{
	if (m_player)
	{
		m_player->Update(dt);
	}

	GET_SINGLE(EnemyManager)->Update(dt);

	GET_SINGLE(BulletManager)->Update(dt);
}

void GameScene::Render(HDC hdc)
{
	if (m_player)
	{
		m_player->Render(hdc);
	}

	GET_SINGLE(EnemyManager)->Render(hdc);

	GET_SINGLE(BulletManager)->Render(hdc);
}

void GameScene::Release()
{
	if (m_player)
	{
		m_player->Release();
	}

	GET_SINGLE(EnemyManager)->Release();

	GET_SINGLE(BulletManager)->Release();
}
