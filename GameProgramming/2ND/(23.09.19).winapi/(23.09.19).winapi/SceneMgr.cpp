#include "pch.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Start_Scene.h"
#include "Game_Scene.h"

void SceneMgr::Init()
{
	m_pCurScene = nullptr;
	//�� ���
	RegisterScene(L"Start Scene", std::make_shared<Start_Scene>());
	RegisterScene(L"Game Scene", std::make_shared<Game_Scene>());

	//ù �� ����
	LoadScene(L"Start_Scene");
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
}

void SceneMgr::Render(HDC _dc)
{
	m_pCurScene->Render(_dc);
}

void SceneMgr::LoadScene(const wstring& _sceneName)
{
	//���� ������
	if (m_pCurScene != nullptr)
	{
		m_pCurScene->Release();
		m_pCurScene = nullptr;
	}

	auto iter = m_mapScenes.find(_sceneName);
	if (iter != m_mapScenes.end())
	{
		m_pCurScene = iter->second;
		m_pCurScene->Init();
	}
}

void SceneMgr::RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), { _sceneName, _scene });
}
