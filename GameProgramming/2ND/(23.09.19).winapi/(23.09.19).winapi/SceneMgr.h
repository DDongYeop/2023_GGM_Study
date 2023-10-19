#pragma once
class Scene;
class SceneMgr
{
private:
	//스마트 포인터
	std::shared_ptr<Scene> m_pCurScene; //현재 씬 
	//씬들을 관리하는 맵
	map<wstring, std::shared_ptr<Scene>> m_mapScenes;
};

