#pragma once
class Object
{
public:
	Object();
	virtual ~Object();
public: //��ġ ũ��
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void Render(HDC _dc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; };
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; };
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
private:
	Vec2 m_vPos;
	Vec2 m_vScale;
};
