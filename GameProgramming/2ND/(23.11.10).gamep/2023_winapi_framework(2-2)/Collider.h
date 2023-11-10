#pragma once
class Object;
class Collider
{
public:
	Collider();
	~Collider();
public:
	void FinalUpdate();
	void Render(HDC _dc);
public:
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetOffSetPos(Vec2 _vOffsetPos) 
	{ m_vOffsetPos = _vOffsetPos; }
	const Vec2& GetScale() const { return m_vScale; }
	const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
private:
	Object* m_pOwner;
	Vec2 m_vOffsetPos; // 오프셋
	Vec2 m_vFinalPos; // 파이널 위치
	Vec2 m_vScale; // 크기
	friend class Object;
};

