#pragma once
class CollisionMgr
{
	SINGLE(CollisionMgr);
public:
	void Update();
	void CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight);
	void CheckReset();
private:
	void CollisionGroupUpdate(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight);
private:
	// 그룹간의 충돌체크할 배열
	UINT m_arrCheck[(UINT)OBJECT_GROUP::END];
};

