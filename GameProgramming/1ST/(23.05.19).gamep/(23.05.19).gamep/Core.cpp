#include<iostream>
#include "Core.h"
#include "console.h"
#include "MapManager.h"
using namespace std;

Core* Core::m_pInst = nullptr;

Core::Core()
{
}

Core::~Core()
{
}

bool Core::Init()
{
	if (!MapManager::GetInst()->Init())
		return false;
	fontsize(300, 35, 35);
	Cursorset(false, 1);
	return true;
}

void Core::Run()
{
	int iStage = MenuDraw();

	while (true)
	{
		if (iStage == 4)
			break;
		MapManager::GetInst()->Run(iStage);
	}
}

int Core::MenuDraw()
{
	cout << "1. Stage1\n";
	cout << "2. Stage2\n";
	cout << "3. Stage3\n";
	cout << "4. Exit\n";
	int iInput;
	cin >> iInput;
	return iInput;
}
