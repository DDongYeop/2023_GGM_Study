#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"
//#include <chrono> // ns
void TimeMgr::Init()
{
	m_llPrevCount = {};
	m_llCurCount = {};
	m_llFrequency = {};	
	m_frameCount = 0;
	m_fps = 0;
	m_accFrameTime = 0.f;
	// 현재 카운트의 틱을 가져온다.(지난시간)
	// 1초 2초 이런 초가 아니야. Frequency로 알아야해.
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수를 반환합니다.
	// 현재 타이머가 동작하는 주파수를 반환합니다. 
	// <-> 주기: 한번 진동하는데 걸리는 시간
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// Delta Time: 한 프레임에 걸린 시간.
	m_dT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// FPS: Frame Per Second
	m_llPrevCount = m_llCurCount;
	//	1. / m_dT;
	m_frameCount++; // 프레임 호출 누적
	m_accFrameTime += m_dT; // 시간 누적
	if (m_accFrameTime >= 1.f) // 1초
	{
		m_fps = m_frameCount / m_accFrameTime;
		m_accFrameTime = 0.f;
		m_frameCount = 0;
		static wchar_t titlebuf[50] = {};		
		swprintf_s(titlebuf, L"FPS: %d, DT: %f", m_fps, m_dT);
		//wsprintf();
		//SetWindowText(Core::GetInst()->GetHwnd(), titlebuf);
	}


}
