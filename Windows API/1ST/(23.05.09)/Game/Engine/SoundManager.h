#pragma once

using namespace FMOD;

class SoundManager
{
	DECLARE_SINGLE(SoundManager);

public:
	void Init();
	void Update(float dt);
	void Release();

public:
	void AddSound(wstring keyName, wstring fileName, bool bgm = false, bool loop = false);

	void Play(wstring keyName, float volume = 1.0f);
	void Stop(wstring keyName);
	void Pause(wstring keyName, bool paused = true);

	bool IsPlaySound(wstring keyName);
	bool IsPauseSound(wstring keyName);

private:
	System*					m_system;

	map<wstring, Sound*>	m_soundContainer;
	map<wstring, Channel*>	m_channelContainer;
};

