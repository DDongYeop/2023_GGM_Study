#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Scene.h"
#include "Collider.h"
void CollisionMgr::Update()
{
	for (UINT Row = 0; Row < (UINT)OBJECT_GROUP::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)OBJECT_GROUP::END; ++Col)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((OBJECT_GROUP)Row, (OBJECT_GROUP)Col);
			}
		}
	}
}
void CollisionMgr::CollisionGroupUpdate(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	std::shared_ptr<Scene> pCurScene = SceneMgr::GetInst()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(_eRight);
	// 충돌 검사를 해보자.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없는 경우
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->GetCollider() == nullptr ||
				vecLeft[i] == vecRight[j])
				continue;
			vecLeft[i]->GetCollider();
			vecRight[j]->GetCollider();
			//if ()
			{
			}//충돌한다면???)
		}
	}
}

void CollisionMgr::CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	// 작은쪽을 행으로 씁시다.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	Row = min(Row, Col);

	//// 비트 연산
	// 체크가 되어있다면
	if (m_arrCheck[Row] &= (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)(OBJECT_GROUP::END));
}

