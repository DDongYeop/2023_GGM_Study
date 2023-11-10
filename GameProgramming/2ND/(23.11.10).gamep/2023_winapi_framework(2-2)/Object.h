#pragma once
class Collider;
class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
	void Component_Render(HDC _dc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	Collider* GetCollider() const 
	{ return m_pCollider; }
public:
	void CreateCollider();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	Collider* m_pCollider;
};

