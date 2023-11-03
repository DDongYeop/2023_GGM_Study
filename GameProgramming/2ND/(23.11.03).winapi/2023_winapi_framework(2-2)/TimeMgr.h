#pragma once
class TimeMgr
{
	SINGLE(TimeMgr);
public:
	void Init();
	void Update();
public:
	const float& GetDT() const { return m_dT; }
private:
	// DT(1프레임당 시간: Delta time)
	LARGE_INTEGER m_llPrevCount; // 이전시간
	LARGE_INTEGER m_llCurCount; // 현재시간
	LARGE_INTEGER m_llFrequency; // 주파수
	float m_dT; // 프레임간의 시간 값

	// FPS
	UINT  m_fps; // FPS
	UINT  m_frameCount; // 프레임 호출 체크
	float m_accFrameTime; // 시간 누적

};

