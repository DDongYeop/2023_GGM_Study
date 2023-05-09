#pragma once

class Timer
{
public:
	Timer();
	~Timer();

public:
	void Init();
	void Update();

public:
	UINT	GetFps() { return m_fps; }
	float	GetDeltaTime() { return m_deltaTime; }

private:
	UINT64	m_frequency = 0;
	UINT64	m_prevCount = 0;
	float	m_deltaTime = 0.0f;

private:
	UINT	m_frameCount = 0;
	float	m_frameTime = 0.0f;
	UINT	m_fps = 0;
};

