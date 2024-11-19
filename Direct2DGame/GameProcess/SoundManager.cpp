#include "GameProcessPCH.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr; //static 변수 초기화

SoundManager::~SoundManager()
{
}
void SoundManager::Initialize()
{
	FMOD::System_Create(&_system);
	_system->init(22, FMOD_INIT_NORMAL, NULL);

	// 변수 초기화

	_backgroundChannel = nullptr;
	_SFXChannels[0] = nullptr;
	_SFXChannels[1] = nullptr;
	_SFXChannels[2] = nullptr;
	_SFXChannels[3] = nullptr;
	_SFXChannels[4] = nullptr;
	_SFXChannels[5] = nullptr;
	_SFXChannels[6] = nullptr;
	_SFXChannels[7] = nullptr;
	_SFXChannels[8] = nullptr;
	_SFXChannels[9] = nullptr;
	_SFXChannels[10] = nullptr;	
	
	_SFXChannels2[0] = nullptr;
	_SFXChannels2[1] = nullptr;
	_SFXChannels2[2] = nullptr;
	_SFXChannels2[3] = nullptr;
	_SFXChannels2[4] = nullptr;
	_SFXChannels2[5] = nullptr;
	_SFXChannels2[6] = nullptr;
	_SFXChannels2[7] = nullptr;
	_SFXChannels2[8] = nullptr;
	_SFXChannels2[9] = nullptr;
	_SFXChannels2[10] = nullptr;
}

SoundManager* SoundManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SoundManager();
	}
	return m_instance;
}

void SoundManager::Finalize()
{
	// 배경음 해제
	for (auto& sound : m_instance->_backgroundSound)
	{
		sound.second->release();
	}
	m_instance->_backgroundSound.clear();

	// 효과음 해제
	for (auto& sound : _SFXSound)
	{
		sound.second->release();
	}
	_SFXSound.clear();
	SoundManager* soundManager = SoundManager::GetInstance();
	delete soundManager;
}

void SoundManager::LoadSound(const wstring& key, const wstring& path, SoundType soundType)
{
	FMOD::Sound* sound; //*

	//std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	//std::string pathString = converter.to_bytes(path);
	string fullPath = "";
	fullPath.assign(path.begin(),path.end());
	
	//_system->createSound(fullPath.c_str(), FMOD_LOOP_OFF, 0, &sound);
	
	
	if (soundType == SoundType::BGM)
	{
		_system->createSound(fullPath.c_str(), FMOD_LOOP_NORMAL, 0, &sound); // 배경음악은 
		_backgroundSound.insert({ key, sound });

	}
	else if (soundType == SoundType::SFX)
	{
		_system->createSound(fullPath.c_str(), FMOD_LOOP_OFF | FMOD_DEFAULT, NULL, &sound);
		_SFXSound.insert({ key, sound });
	}
}

void SoundManager::PlayBackgroundSound(const wstring& key)
{
	//값 검색
	auto it = _backgroundSound.find(key);
	_system->playSound(it->second, 0, false, &_backgroundChannel);
	
}

void SoundManager::PlaySFXSound(const wstring& key,int channelNum ,int channelIndex)
{
	auto it = _SFXSound.find(key);
	if(channelNum == 1)
		_system->playSound(it->second, 0, false, &_SFXChannels[channelIndex]);
	else if(channelNum ==2)
		_system->playSound(it->second, 0, false, &_SFXChannels2[channelIndex]);
}

void SoundManager::PauseSFXSound(int channelIndex)
{
	if (channelIndex >= 0 && channelIndex < 10)
	{
		_SFXChannels2[channelIndex]->setMute(true);
	}

}
bool SoundManager::isPlayingBGM()
{
	bool isPlaying;
	_backgroundChannel->isPlaying(&isPlaying);
	return isPlaying;
}
bool SoundManager::isPlayingChannel(int index)
{
	bool isPlaying;
	_SFXChannels[index]->isPlaying(&isPlaying);
	return isPlaying;
}
bool SoundManager::isPlayingChannel2(int index)
{
	bool isPlaying;
	_SFXChannels2[index]->isPlaying(&isPlaying);
	return isPlaying;
}

void SoundManager::SetBGMVolume(float sVolume)
{
	float volume = m_instance->fVolume;
	fVolume = sVolume;
	// 배경음 설정
	_backgroundChannel->setVolume(sVolume);

// 	// 효과음 채널들 설정
// 	for (auto& channel : _SFXChannels)
// 	{
// 		channel->setVolume(sVolume);
// 	}
}

void SoundManager::GetVolume(float* sVolume)
{
	float volume = m_instance->fVolume;
	fVolume = 0.1f;
	*sVolume = fVolume;

	// 배경음 설정
	_backgroundChannel->getVolume(sVolume);

	// 효과음 채널들 설정
	for (auto& channel : _SFXChannels)
	{
		channel->getVolume(sVolume);
	}
}

void SoundManager::SetSFXVolume(float sVolume, int index)
{
	 	for (auto& channel : _SFXChannels2)
 	{
 		channel->setVolume(sVolume);
 	}




// 	float volume = m_instance->fVolume;
// 	fVolume = sVolume;
// 	_SFXChannels2[index]->setVolume(sVolume);
}

// void SoundManager::BGMPlay()
// {
// 	PlayBackgroundSound(L"bgm2");
// }



//void SoundManager::PauseMusic()
//{
//	_backgroundChannel->pause();
//}

// void SoundManager::PauseSFX(int index)
// {
// 	_SFXChannels2[index]->Setpause();
// }
