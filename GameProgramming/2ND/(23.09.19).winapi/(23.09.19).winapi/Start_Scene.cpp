#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"

void Start_Scene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({ 1280 / 2, Core::GetInst()->GetResolution().y / 2 })));
	pObj->SetScale(Vec2(100.0f, 100.0f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Monster* pMonster = new Monster;
	int iMonster = 5;		//몬스터 수
	float fMoveDist = 10.f; //거리
	float fMonsterScale = 50.f; //크기
	//해성도x - (움직일거리 + 오브젝트크기/2) * 2 / 수 -1
	float fTerm = (vResolution.x - (fMoveDist + fMonsterScale / 2.f) * 2.f) / (float)(iMonster - 1);
	for (int i = 0; i < iMonster; ++i)
	{
		pMonster = new Monster;
		pMonster->SetPos(Vec2((fMoveDist + fMonsterScale / 2.f) + i * fTerm, 50.f));
		pMonster->SetCenterPos(pMonster->GetPos());
		pMonster->SetMoveDis(fMoveDist);
		pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
		AddObject(pMonster, OBJECT_GROUP::MONSTER);
	}
}
