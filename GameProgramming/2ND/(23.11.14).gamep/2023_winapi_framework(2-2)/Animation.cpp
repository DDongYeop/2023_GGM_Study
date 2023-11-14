#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
#include "TimeMgr.h"
#include "Animator.h"

Animation::Animation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0)
	, m_repeatcnt(0)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	m_fAccTime += fDT;
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame;
		if (m_CurFrame >= m_vecAnimFrame.size())

		{
			m_CurFrame = 0;
			m_fAccTime = 0.f;
		}
	}
}

void Animation::Render(HDC _dc)
{
	Object* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	TransparentBlt(_dc
		, (int)(vPos.x - m_vecAnimFrame[m_CurFrame].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecAnimFrame[m_CurFrame].vSlice.y / 2.f)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.y)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
		, RGB(255, 0, 255));

}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _framecount, float _fDuration)
{
	m_pTex = _pTex;
	for (int i = 0; i < _framecount; ++i)
	{
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i, _vSliceSize, _fDuration }));
	}
}
