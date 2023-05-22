#pragma once
#include "define.h"

class Core
{
private:
	Core();
	~Core();
public:
	static Core* m_pInst;
public:
	static Core* GetInst()
	{
		if (m_pInst == nullptr)
			m_pInst = new Core;
		return m_pInst;
	}
public:
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
		/*if (m_pInst)
		{
			delete m_pInst;
			m_pInst = nullptr;
		}*/
	}
public:
	bool Init();
	void Run();
	int MenuDraw();
};
