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
	vector<POINT>	m_frameList;	// ������ ����
	vector<int>		m_playList;		// ��� �ε��� ����

	int				m_frameCount;	// ������ ����
	int				m_frameWidth;	// ������ ����ũ��
	int				m_frameHeight;	// ������ ����ũ��

	float			m_fUpdateTime;	// ������ ���� �ð�
	float			m_fElapsedTime;	// ���� �ð�

	int				m_nowIndex;		// ���� ��� �ε���
	BOOL			m_isPlay;		// �ִϸ��̼� ��� ����
	BOOL			m_isLoop;		// �ִϸ��̼� ���� ����
};

