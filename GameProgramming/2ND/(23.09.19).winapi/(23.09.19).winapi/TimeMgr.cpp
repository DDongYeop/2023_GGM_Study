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
	//���� ī������ ƽ�� �����´�. (���� �ð�)
	//1�� 2�� �̷� �ʰ� �ƴ϶� Frequency�� �˾ƾ���
	QueryPerformanceCounter(&m_llPrevCount);

	//�ʴ� ī��Ʈ Ƚ�� ��ȯ
	//���� Ÿ�̸Ӱ� �����ϴ� ���ļ� ��ȯ 
	//<-> �ֱ�: �ѹ� �����ϴµ� �ɸ��� �ð�
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//Delta Time: �� �����ӿ� �ɸ� �ð�
	m_dT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// FPS: Frame Per Second
	m_llPrevCount = m_llCurCount;
	// 1. / m_dT
	m_frameCount++; //������ ȣ�� ����
	m_accFrameTIme += m_dT; //�ð� ����
	if (m_accFrameTIme >= 1.f) //1��
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
