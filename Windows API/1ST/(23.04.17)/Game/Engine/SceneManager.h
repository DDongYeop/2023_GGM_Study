#pragma once
class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager)

public:
	void RegisterScene(const wstring& sceneName, shared_ptr<Scene> scene);
	void LoadScene(const wstring& sceneName);

public:
	void	Init();
	void	Update(float dt);
	void	Render(HDC hdc);
	void	Release();

private:
	shared_ptr<Scene>				m_activeScene;
	map<wstring, shared_ptr<Scene>> m_sceneContainer;
};

