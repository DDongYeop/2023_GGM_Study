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
			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();
			COLLIDER_ID colID;
			colID.left_ID = pLeftCol->GetID();
			colID.right_ID = pRightCol->GetID();

			// 찾아라.
			auto iter = m_mapColInfo.find(colID.ID);
			// 없어용
			if (iter == m_mapColInfo.end())
			{
				// 넣어라
				m_mapColInfo.insert({ colID.ID, false });
				// 넣은거 잡아라.
				iter = m_mapColInfo.find(colID.ID);
			}
			// 충돌하네?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 이전에도 충돌 중
				if (iter->second)
				{
					//둘중 하나가 삭제 예정이면
					if (vecLeft[i]->GetIsDead() || vecRight[j]->GetIsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->StayCollision(pRightCol);
						pRightCol->StayCollision(pLeftCol);
					}
				}
				// 이전에 충돌x
				else
				{
					pLeftCol->EnterCollision(pRightCol);
					pRightCol->EnterCollision(pLeftCol);
					iter->second = true;
				}
			}
			// 안하네?
			else
			{
				if (iter->second)
				{
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight)
{
	// 충돌검사 알고리즘
	// AABB 
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();
	Vec2 vRightScale = _pRight->GetScale();
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CollisionMgr::CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight)
{
	// 작은쪽을 행으로 씁시다.
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	Row = min(Row, Col);

	//// 비트 연산
	// 체크가 되어있다면
	if (m_arrCheck[Row] & (1 << Col))
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

