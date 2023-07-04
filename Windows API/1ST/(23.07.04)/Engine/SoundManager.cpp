#include "pch.h"
#include "SoundManager.h"

void SoundManager::Init()
{
	System_Create(&m_system);

	if (m_system)
		m_system->init(100, FMOD_INIT_NORMAL, nullptr);
}

void SoundManager::Update(float dt)
{
	if (m_system)
		m_system->update();
}

void SoundManager::Release()
{
	// 채널을 이용해서 재생중인 사운드 정지
	map<wstring, Channel*>::iterator iterCh;
	for (iterCh = m_channelContainer.begin(); iterCh != m_channelContainer.end(); ++iterCh)
		iterCh->second->stop();

	// 사운드를 이용하여 음원 제거
	map<wstring, Sound*>::iterator iterSo;
	for (iterSo = m_soundContainer.begin(); iterSo != m_soundContainer.end(); ++iterSo)
		iterSo->second->release();

	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}
}

void SoundManager::AddSound(wstring keyName, wstring fileName, bool bgm, bool loop)
{
	if (m_system == NULL)
		return;

	Sound* sound;
	if (loop)
	{
		if (bgm)
		{
			m_system->createStream(ws2s(fileName).c_str(), FMOD_LOOP_NORMAL, NULL, &sound);
		}
		else
		{
			m_system->createSound(ws2s(fileName).c_str(), FMOD_LOOP_NORMAL, NULL, &sound);
		}
	}
	else
	{
		m_system->createSound(ws2s(fileName).c_str(), FMOD_DEFAULT, NULL, &sound);
	}

	m_soundContainer.insert(make_pair(keyName, sound));
	m_channelContainer.insert(make_pair(keyName, nullptr));
}

void SoundManager::Play(wstring keyName, float volume)
{
	auto iterSo = m_soundContainer.find(keyName);
	auto iterCh = m_channelContainer.find(keyName);

	if (iterSo != m_soundContainer.end() && iterCh != m_channelContainer.end())
	{
		m_system->playSound(iterSo->second, 0, false, &iterCh->second);
		if(iterCh->second)
			iterCh->second->setVolume(volume);
	}
}

void SoundManager::Stop(wstring keyName)
{
	auto iterCh = m_channelContainer.find(keyName);
	if (iterCh != m_channelContainer.end())
	{
		if(iterCh->second)
			iterCh->second->stop();
	}
}

void SoundManager::Pause(wstring keyName, bool paused)
{
	auto iterCh = m_channelContainer.find(keyName);
	if (iterCh != m_channelContainer.end())
	{
		if (iterCh->second)
			iterCh->second->setPaused(paused);
	}
}

bool SoundManager::IsPlaySound(wstring keyName)
{
	bool isPlay = false;

	auto iterCh = m_channelContainer.find(keyName);
	if (iterCh != m_channelContainer.end())
	{
		if (iterCh->second)
			iterCh->second->isPlaying(&isPlay);
	}
	return isPlay;
}

bool SoundManager::IsPauseSound(wstring keyName)
{
	bool isPause = false;

	auto iterCh = m_channelContainer.find(keyName);
	if (iterCh != m_channelContainer.end())
	{
		if (iterCh->second)
			iterCh->second->getPaused(&isPause);
	}
	return isPause;
}
