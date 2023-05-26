#include "MapManager.h"
#include "Stage.h"
#include "console.h"
MapManager* MapManager::m_pInst = nullptr;

MapManager::MapManager() : m_iCurStage(0)
{
	for (int i = 0; i < STAGE_MAX_COUNT; i++)
	{
		m_pStage[i] = nullptr;
	}
}

MapManager::~MapManager()
{
}

bool MapManager::Init()
{
	char* pStageFile[STAGE_MAX_COUNT] = { (char*)"Stage1.txt", (char*)"Stage2.txt", (char*)"Stage3.txt" };
	for (int i = 0; i < STAGE_MAX_COUNT; i++)
	{
		m_pStage[i] = new Stage;
		if (!m_pStage[i]->Init(pStageFile[i]))
		{
			return false;
		}
	}
	return true;
}

void MapManager::Run(int _iCurStage)
{
	m_iCurStage = _iCurStage;
	while (true)
	{
		Gotoxy(0, 0);
		m_pStage[_iCurStage]->Render();

	}
}
