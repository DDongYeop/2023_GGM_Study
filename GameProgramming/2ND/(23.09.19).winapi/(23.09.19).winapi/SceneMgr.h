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
	void LoadScene(const wstring& _sceneName);
	void RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene);
public:
	const std::shared_ptr<Scene>& GetCurScnee() const { return m_pCurScene; };
private:
	//����Ʈ ������
	std::shared_ptr<Scene> m_pCurScene; //���� �� 
	//������ �����ϴ� ��
	map<wstring, std::shared_ptr<Scene>> m_mapScenes;
};

