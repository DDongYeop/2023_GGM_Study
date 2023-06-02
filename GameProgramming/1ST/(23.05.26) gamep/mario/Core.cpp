#include <iostream>
#include "Core.h"
#include "console.h"
#include "MapManager.h"
#include "ObjectManager.h"
using namespace std;
//Core core;
Core* Core::m_pInst = nullptr;

Core::Core()
{
}

Core::~Core()
{
}

bool Core::Init()
{
	// ?? 
	// 맵생성..
	if (!MapManager::GetInst()->Init())
		return false;
	if (!ObjectManager::GetInst()->Init())
		return false;
	// 플레이어 생성.. 미리 해야되는것들
	fontsize(300,35,35);
	system("mode con cols=80 lines=30");
	Cursorset(false, 1);
	return true;
}

void Core::Run()
{
	int iStage = MenuDraw();
	// 맵을 그려줄겁니다.
	// 스테이지가 필요해.
	system("cls");
	while (true)
	{
		if (iStage == 4)
			break;
		MapManager::GetInst()->Run(iStage-1);
	}
}

int Core::MenuDraw()
{
	cout << "1. Stage1" << endl;
	cout << "2. Stage2" << endl;
	cout << "3. Stage3" << endl;
	cout << "4. Exit" << endl;
	int iInput;
	cin >> iInput;
	return iInput;
}
