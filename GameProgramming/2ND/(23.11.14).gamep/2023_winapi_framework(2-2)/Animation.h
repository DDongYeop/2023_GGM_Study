#pragma once

struct tAnimFrame
{
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration;
};

class Texture;
class Animator;
class Animation
{
public:
	Animation();
	~Animation();
public:
	void Update();
	void Render(HDC _dc);
	friend class Animator;
public:
	void Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _framecount, float _fDuration);
public:
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
private:
	UINT m_CurFrame;
	float m_fAccTime;
	int m_repeatcnt;
	Texture* m_pTex;
	vector<tAnimFrame> m_vecAnimFrame;
	wstring m_strName;
	Animator* m_pAnimator;
	friend class Animator;
};

