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
	// �ʻ���..
	if (!MapManager::GetInst()->Init())
		return false;
	if (!ObjectManager::GetInst()->Init())
		return false;
	// �÷��̾� ����.. �̸� �ؾߵǴ°͵�
	fontsize(300,35,35);
	system("mode con cols=80 lines=30");
	Cursorset(false, 1);
	return true;
}

void Core::Run()
{
	int iStage = MenuDraw();
	// ���� �׷��̴ٰϴ�.
	// ���������� �ʿ���.
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
