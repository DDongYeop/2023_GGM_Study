#pragma once
class Scene;
class SceneMgr
{
	SINGLE(SceneMgr);
public:
	void Init();
	void Update();
	void Render(HDC _dc);
public:
	void LoadScene(const wstring& _scenename);
	void RegisterScene(const wstring& _scenename, std::shared_ptr<Scene> _scene);
public:
	const std::shared_ptr<Scene>& GetCurScene() const
	{
		return m_pCurScene;
	}
private:
	// 스마트 포인터
	std::shared_ptr<Scene> m_pCurScene; // 현재 씬
	// 씬들을 관리하는 맵.
	map<wstring, std::shared_ptr<Scene>> m_mapScenes;
};