#pragma once

class Animation
{
public:
	Animation();
	~Animation();
	
public:
	void Init(int width, int height, int frameW, int frameH);
	void Update(float dt);
	void Release();

public:
	void Start();
	void Stop();
	void Pause();
	void Resume();

public:
	void SetPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void SetUpdateTime(float time);

public:
	inline BOOL IsPlay() { return m_isPlay; }
	inline POINT GetFramePos()
	{
		if (m_nowIndex < 0 || m_nowIndex >= m_playList.size())
			return POINT{ -1 - 1 };
		return m_frameList[m_playList[m_nowIndex]];
	}

	inline int GetFrameWidth() { return m_frameWidth; }
	inline int GetFrameHeight() { return m_frameHeight; }

private:
	vector<POINT>	m_frameList;	// 프레임 저장
	vector<int>		m_playList;		// 재생 인덱스 저장

	int				m_frameCount;	// 프레임 갯수
	int				m_frameWidth;	// 프레임 가로크기
	int				m_frameHeight;	// 프레임 세로크기

	float			m_fUpdateTime;	// 프레임 갱신 시간
	float			m_fElapsedTime;	// 누적 시간

	int				m_nowIndex;		// 현재 재생 인덱스
	BOOL			m_isPlay;		// 애니메이션 재생 여부
	BOOL			m_isLoop;		// 애니메이션 루프 여부
};

