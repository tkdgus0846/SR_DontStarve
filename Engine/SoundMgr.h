#pragma once

#include "Include.h"

BEGIN(Engine)

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

private:
	explicit CSoundMgr(void);
	virtual ~CSoundMgr(void);

public:
	void Init(); 
	void Release(); 

public:
	void PlayGameSound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
	void StopAllBGM();

	bool IsPlaying(CHANNELID eID);

private:
	void LoadSoundFile(); 

private:

	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 

	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem; 
};

#define SOUND CSoundMgr::GetInstance()
#define PLAY_SOUND(soundkey, channelID, volume) SOUND->PlayGameSound(soundkey, channelID, volume)
#define PLAY_BGM(soundKey, channelID, volume) SOUND->PlayBGM(soundKey, channelID, volume)
#define STOP_SOUND(channelID) SOUND->StopSound(channelID)
#define STOP_ALL_SOUND SOUND->StopAll()
#define SET_CHANNEL_VOLUME(channelID, volume) SOUND->SetChannelVolume(channelID, volume)

#define STOP_ALL_BGM SOUND->StopAllBGM()

#define STOP_PLAY_SOUND(soundkey, channelID, volume)        \
STOP_SOUND(channelID);											\
PLAY_SOUND(soundkey, channelID, volume)							\

#define IS_PLAYING(channelID) SOUND->IsPlaying(channelID)


END