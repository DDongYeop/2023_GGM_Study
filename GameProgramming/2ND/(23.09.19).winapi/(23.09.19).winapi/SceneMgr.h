#pragma once
class Scene;
class SceneMgr
{
private:
	//����Ʈ ������
	std::shared_ptr<Scene> m_pCurScene; //���� �� 
	//������ �����ϴ� ��
	map<wstring, std::shared_ptr<Scene>> m_mapScenes;
};

