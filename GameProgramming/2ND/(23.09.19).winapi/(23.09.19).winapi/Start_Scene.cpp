#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"

void Start_Scene::Init()
{
	Object* pObj = new Object;
	pObj->SetPos((Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 })));
	pObj->SetScale(Vec2(100.0f, 100.0f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);
}
