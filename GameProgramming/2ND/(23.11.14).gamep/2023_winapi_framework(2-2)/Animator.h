#pragma once
class Object;
class Animation;
class Texture;

class Animator
{
public:
	Animator();
	~Animator();
public:
	void Update();
	void Render(HDC _dc);
public:
	//생성
	void CreateAnim(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _framecount, float  _fDuration);
	//찾기
	Animation* FindAnim(const wstring& _strName);
	//플레이 함수
	void PlayAnim(const wstring& _strName, bool _bRepeat);
	Object* GetObj() const { return m_pOwner; }
private:
	map<wstring, Animation*> m_mapAnim;
	Animation* m_pCurAnim;
	Object* m_pOwner;
	friend class Object;
	bool m_IsRepeat;
};

