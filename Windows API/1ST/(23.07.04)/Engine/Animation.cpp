#include "pch.h"
#include "Animation.h"

Animation::Animation()
{
	m_frameCount = 0;
	m_frameWidth = 0;
	m_frameHeight = 0;
	m_fUpdateTime = 0.1f;
	m_fElapsedTime = 0.0f;
	m_nowIndex = 0;
	m_isPlay = FALSE;
	m_isLoop = FALSE;
}

Animation::~Animation()
{
}

void Animation::Init(int width, int height, int frameW, int frameH)
{
	m_frameWidth = frameW;
	int wCount = width / frameW;

	m_frameHeight = frameH;
	int hCount = height / frameH;

	m_frameCount = wCount * hCount;

	for (int i = 0; i < hCount; ++i)
	{
		for (int j = 0; j < wCount; ++j)
		{
			POINT framePos;
			framePos.x = j * m_frameWidth;
			framePos.y = i * m_frameHeight;
			m_frameList.push_back(framePos);
		}
	}
}

void Animation::Update(float dt)
{
	if (m_isPlay)
	{
		m_fElapsedTime += dt;
		if (m_fElapsedTime >= m_fUpdateTime)
		{
			m_fElapsedTime = 0.0f;
			m_nowIndex++;
			if (m_nowIndex >= m_playList.size())
			{
				if (m_isLoop)
				{
					m_nowIndex = 0;
				}
				else
				{
					m_nowIndex--;
					m_isPlay = FALSE;
				}
			}
		}
	}
}

void Animation::Release()
{
}

void Animation::Start()
{
	m_isPlay = TRUE;
	m_nowIndex = 0;
}

void Animation::Stop()
{
	m_isPlay = FALSE;
	m_nowIndex = 0;
}

void Animation::Pause()
{
	m_isPlay = FALSE;
}

void Animation::Resume()
{
	m_isPlay = TRUE;
}

void Animation::SetPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	m_playList.clear();

	m_isLoop = loop;

	if (start > end)
	{
		if (reverse)
		{
			for (int i = start; i >= end; --i)
				m_playList.push_back(i);
		}
		else
		{
			for (int i = end; i <= start; ++i)
				m_playList.push_back(i);
		}
	}
	else
	{
		if (reverse)
		{
			for (int i = end; i >= start; --i)
				m_playList.push_back(i);
		}
		else
		{
			for (int i = start; i <= end; ++i)
				m_playList.push_back(i);
		}
	}

}

void Animation::SetUpdateTime(float time)
{
	m_fUpdateTime = time;
}
