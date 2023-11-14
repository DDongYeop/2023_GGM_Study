#include "pch.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator() : m_pOwner(nullptr)
{
}

Animator::~Animator()
{
	map<wstring, Animation*>::iterator iter;
	for (iter = m_mapAnim.begin(); iter != m_mapAnim.end(); ++iter)
	{
		if (iter->second != nullptr)
			delete iter->second;
	}
	m_mapAnim.clear();
}

void Animator::Update()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Update();
	}
}

void Animator::Render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->Render(_dc);
	}
}

void Animator::CreateAnim(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _framecount, float  _fDuration)
{
	Animation* pAnim = FindAnim(_strName);
	if (pAnim != nullptr)
		return;
	pAnim = new Animation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _framecount, _fDuration);
	m_mapAnim.insert({ _strName, pAnim });
}

Animation* Animator::FindAnim(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
		return nullptr;
	return nullptr;
}

void Animator::PlayAnim(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnim(_strName);
	m_IsRepeat = _bRepeat;
}
