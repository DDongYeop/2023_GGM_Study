#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::RegisterScene(const wstring& sceneName, shared_ptr<Scene> scene)
{
	if (sceneName.empty() || scene == NULL)
		return;

	m_sceneContainer.insert(m_sceneContainer.end(), pair <wstring, shared_ptr<Scene>>(sceneName, scene));
}

void SceneManager::LoadScene(const wstring& sceneName)
{
	if (m_activeScene != NULL)
	{
		m_activeScene->Release();
		m_activeScene = NULL;
	}

	auto it = m_sceneContainer.find(sceneName);
	if (it != m_sceneContainer.end())
	{
		m_activeScene = it->second;
		m_activeScene->Init();
	}
}

void SceneManager::Init()
{
	m_activeScene = NULL;
}

void SceneManager::Update(float dt)
{
	if (m_activeScene == NULL)
		return;

	m_activeScene->Update(dt);
}

void SceneManager::Render(HDC hdc)
{
	if (m_activeScene == NULL)
		return;

	m_activeScene->Render(hdc);
}

void SceneManager::Release()
{
	m_activeScene = NULL;
}
