#pragma once
#include "define.h"
class Player;
class ObjectManager
{
private:
	ObjectManager();
	~ObjectManager();
private:
	static ObjectManager* m_pInst;
	Player* m_pPlayer;
public:
	static ObjectManager* GetInst()
	{
		if (m_pInst == nullptr)
			m_pInst = new ObjectManager;
		return m_pInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}
	Player* GetPlayer() { return m_pPlayer; }
public:
	bool Init();
	void Update();
};

