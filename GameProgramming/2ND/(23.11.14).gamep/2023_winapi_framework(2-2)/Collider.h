#pragma once
class Object;

class Collider
{
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
	Collider& operator = (Collider& _origin) = delete;
public:
	void FinalUpdate();
	void Render(HDC _dc);
public:
	void EnterCollision(Collider* _pOther);
	void ExitCollision(Collider* _pOther);
	void StayCollision(Collider* _pOther);
public:
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetOffSetPos(Vec2 _vOffsetPos) 
	{ m_vOffsetPos = _vOffsetPos; }
	const Vec2& GetScale() const { return m_vScale; }
	const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
	const Vec2& GetFinalPos() const 
	{ return m_vFinalPos; }
	const UINT& GetID() const { return m_ID; }
	const Object* GetObj() const { return m_pOwner; }
private:
	UINT m_check;
	UINT m_ID; // 충돌체 ID값
	static UINT m_sNextID; 
	Object* m_pOwner;
	Vec2 m_vOffsetPos; // 오프셋
	Vec2 m_vFinalPos; // 파이널 위치
	Vec2 m_vScale; // 크기
	friend class Object;
};

