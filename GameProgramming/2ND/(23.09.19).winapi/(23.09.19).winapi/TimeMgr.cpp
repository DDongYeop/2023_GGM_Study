#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"

void TimeMgr::Init()
{
	m_llPrevCount = {};
	m_llCurCount = {};
	m_llFrequency = {};		
	m_frameCount = 0;
	m_fps = 0;
	m_accFrameTIme = 0.f;
	//현재 카운터의 틱을 가져온다. (지난 시간)
	//1초 2초 이런 초가 아니라 Frequency로 알아야함
	QueryPerformanceCounter(&m_llPrevCount);

	//초당 카운트 횟수 반환
	//현재 타이머가 동작하는 주파수 반환 
	//<-> 주기: 한번 진동하는데 걸리는 시간
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//Delta Time: 한 프레임에 걸린 시간
	m_dT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// FPS: Frame Per Second
	m_llPrevCount = m_llCurCount;
	// 1. / m_dT
	m_frameCount++; //프레임 호출 누적
	m_accFrameTIme += m_dT; //시간 누적
	if (m_accFrameTIme >= 1.f) //1초
	{
		m_fps = m_frameCount / m_accFrameTIme;
		m_accFrameTIme = 0.f;
		m_frameCount = 0;
		m_frameCount = 0;
		static wchar_t titlebuf[50] = {};
		swprintf_s(titlebuf, L"FPS: %d, DT: %d", m_fps, m_dT);
		SetWindowText(Core::GetInst()->GetHwnd(), titlebuf);
	}
}
