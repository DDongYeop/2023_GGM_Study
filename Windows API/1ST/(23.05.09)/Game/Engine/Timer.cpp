#include "pch.h"
#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Init()
{
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_prevCount));
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_frequency));
}

void Timer::Update()
{
	UINT64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	m_deltaTime = (currentCount - m_prevCount) / static_cast<float>(m_frequency);
	m_prevCount = currentCount;

	m_frameCount++;
	m_frameTime += m_deltaTime;

	if (m_frameTime > 1.0f)
	{
		m_fps = static_cast<UINT>(m_frameCount / m_frameTime);
		m_frameCount = 0;
		m_frameTime = 0.0f;
	}
}
