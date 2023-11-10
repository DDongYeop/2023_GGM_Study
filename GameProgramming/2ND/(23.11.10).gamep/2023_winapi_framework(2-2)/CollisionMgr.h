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
	// �׷찣�� �浹üũ�� �迭
	UINT m_arrCheck[(UINT)OBJECT_GROUP::END];
};

