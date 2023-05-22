#include<fstream>
#include "Stage.h"

Stage::Stage() : m_cStage{}, m_tStart{}, m_tEnd{}
{
}

Stage::~Stage()
{
}

bool Stage::Init(char* pFileName)
{
    std::ifstream readfile;
    if (readfile.is_open())
        return false;
    readfile.open(pFileName);
    for (int i = 0; i < 10; i++)
    {
        readfile.getline(m_cStage[i], 51);
        for (int j = 0; j < 50; j++)
        {
            if (m_cStage[i][j] == (char)STAGE_TYPE::START)
            {
                m_tStart.x = i;
                m_tStart.y = i;
            }
            else if (m_cStage[i][j] == (char)STAGE_TYPE::START)
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
}
