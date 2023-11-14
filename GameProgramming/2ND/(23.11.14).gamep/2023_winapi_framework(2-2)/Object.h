#pragma once
class Collider;
class Animator;
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
	virtual void EnterCollision(Collider* _pOther);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);
	void Component_Render(HDC _dc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	Collider* GetCollider() const 
	{ return m_pCollider; }
	Animator* GetAnimator() const
	{return m_pAnimator;}
	const wstring& GetName() const{ return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	const bool& GetIsDead() const{ return m_IsAlive; }
private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
public:
	void CreateCollider();
	void CreateAnimator();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	Collider* m_pCollider;
	wstring m_strName; //이름
	bool m_IsAlive;
	Animator* m_pAnimator;
};

