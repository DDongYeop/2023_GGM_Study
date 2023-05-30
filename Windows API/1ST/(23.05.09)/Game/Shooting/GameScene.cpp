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

	m_eStage = GAME_STAGE::STAGE_01;

	m_player = make_shared<Player>(250, 600, 0, 0, .75f, 200.0f);
	if (m_player)
	{
		m_player->Init();
	}

	GET_SINGLE(BulletManager)->Init();

	GET_SINGLE(BulletManager)->AddPawn(m_player);

	GET_SINGLE(EnemyManager)->Init(m_player, m_eStage);

	GET_SINGLE(SoundManager)->AddSound(L"hit", L"Resources/Sound/hit.wav");
}

void GameScene::Update(float dt)
{
	if (m_player)
	{
		m_player->Update(dt);

		if (m_player->GetHP() <= 0)
			GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
	}

	GET_SINGLE(EnemyManager)->Update(dt);
	if (GET_SINGLE(EnemyManager)->GetEnemies().empty() == true)
	{
		int stage = static_cast<int>(m_eStage);
		m_eStage = static_cast<GAME_STAGE>(++stage);
		GET_SINGLE(EnemyManager)->CreateEnemy(m_eStage);
	}

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
	m_player = nullptr;

	GET_SINGLE(EnemyManager)->Release();

	GET_SINGLE(BulletManager)->Release();

	GET_SINGLE(ImageManager)->DeleteAll();
}
