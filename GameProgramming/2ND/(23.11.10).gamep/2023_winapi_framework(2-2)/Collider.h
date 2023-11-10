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
	Vec2 m_vOffsetPos; // ������
	Vec2 m_vFinalPos; // ���̳� ��ġ
	Vec2 m_vScale; // ũ��
	friend class Object;
};

