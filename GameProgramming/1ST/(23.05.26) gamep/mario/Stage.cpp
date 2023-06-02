#include<fstream>
#include "Stage.h"
#include<iostream>
#include "Player.h"
#include "ObjectManager.h"
using namespace std;
Stage::Stage()
	: m_cStage{}
	, m_tStart{}
	, m_tEnd{}
{
}

Stage::~Stage()
{
}

bool Stage::Init(char* pFileName)
{
	std::ifstream readfile;
	if(readfile.is_open())
		return false;
	readfile.open(pFileName);
	for (int i = 0; i < 10; i++)
	{
		readfile.getline(m_cStage[i], 51);
		for (int j = 0; j < 50; j++)
		{
			if (m_cStage[i][j] == (char)STAGE_TYPE::START)
			{
				m_tStart.x = j;
				m_tStart.y = i;
			}
			else if (m_cStage[i][j] == (char)STAGE_TYPE::END)
			{
				m_tEnd.x = j;
				m_tEnd.y = i;
			}

		}
	}
	return true;
}

void Stage::Render()
{
	Player* pPlayer = ObjectManager::GetInst()->GetPlayer();
	int iPlayerx = pPlayer->GetX();
	int iPlayery = pPlayer->GetY();
	for (int i = 4; i < 10; i++)
	{
		for (int j = iPlayerx; j < iPlayerx + RENDER_MAP_X; j++)
		{
			if (i == iPlayery && j == iPlayerx)
				cout << "¡×";
			else if (m_cStage[i][j] == (char)STAGE_TYPE::WALL)
			{
				cout << "¡á";
			}
			else if (m_cStage[i][j] == (char)STAGE_TYPE::ROAD)
			{
				cout << "  ";
			}
			else if (m_cStage[i][j] == (char)STAGE_TYPE::START)
			{
				cout << "¢ç";
			}
			else if (m_cStage[i][j] == (char)STAGE_TYPE::END)
			{
				cout << "¢Í";
			}
			else  if (m_cStage[i][j] == (char)STAGE_TYPE::COIN)
			{
				cout << "¢Á";
			}
		}
		cout << endl;
	}
}
