#include "AudioManager.h"
#include <iostream>

#pragma comment(lib, "fmodvc.lib")

CAudioManager::CAudioManager(int InitLoopVolume, int InitOnceVolume, int MaxChannel)
:
m_MaxChannel(MaxChannel),
m_LoopVolume(InitLoopVolume),
m_OnceVolume(InitOnceVolume)
{
	//FMOD��ʼ��
	FSOUND_Init(44100, MaxChannel, 0);
}

CAudioManager::~CAudioManager()
{
	std::map<std::string, _LOOPAUDIO>::iterator i;
	for (i = m_LoopAudio.begin(); i != m_LoopAudio.end(); ++i)
		FSOUND_Stream_Close(i->second._s);

	std::map<std::string, FSOUND_SAMPLE*>::iterator j;
	for (j = m_OnceAudio.begin(); j != m_OnceAudio.end(); ++j)
		FSOUND_Sample_Free(j->second);
	
	//FMOD�ر�
	FSOUND_Close();
}

bool CAudioManager::PushLoopAudio(const char* Key, const char* AudioPath)
{
	std::string s = Key;

	//���Key�Ѿ����ڷ���ʧ��
	if (m_LoopAudio.find(Key) != m_LoopAudio.end())
		return false;

	_LOOPAUDIO la;

	//������ʽ��Ƶ
	la._s = FSOUND_Stream_Open(AudioPath, FSOUND_LOOP_NORMAL, 0, 0);

	//����������
	if (la._s)
	{
		m_LoopAudio[s] = la;

		return true;
	}
	else
		return false;
}

bool CAudioManager::PushOnceAudio(const char* Key, const char* AudioPath)
{
	std::string s = Key;

	//���Key�Ѿ����ڷ���ʧ��
	if (m_OnceAudio.find(Key) != m_OnceAudio.end())
		return false;

	//������Ƶ����
	FSOUND_SAMPLE* pFS = FSOUND_Sample_Load(FSOUND_FREE, AudioPath, FSOUND_LOOP_OFF, 0, 0);

	if (pFS)
	{
		m_OnceAudio[s] = pFS;
		return true;
	}
	else
		return false;
}

bool CAudioManager::ReleaseLoopAudio(const char* Key)
{
	std::string s = Key;

	//û���ҵ�
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if (i == m_LoopAudio.end())
		return false;

	FSOUND_Stream_Close(i->second._s);

	m_LoopAudio.erase(i);

	return true;
}

bool CAudioManager::ReleaseOnceAudio(const char* Key)
{
	std::string s = Key;

	//û���ҵ�
	std::map<std::string, FSOUND_SAMPLE*>::iterator i = m_OnceAudio.find(s);
	if (i == m_OnceAudio.end())
		return false;

	FSOUND_Sample_Free(i->second);

	m_OnceAudio.erase(i);
	
	return true;
}

bool CAudioManager::PlayLoopAudio(const char* Key)
{
	//�����ǰ��ѭ����Ƶ�ڲ��ŷ���ʧ��
	if (m_PlayingLoopAudio != std::string(""))
		return false;

	//�޷��ҵ�Key��ָ������Ƶ�򷵻�ʧ��
	std::string s = Key;
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if (i == m_LoopAudio.end())
		return false;

	//���õ�ǰ���ڲ��ŵ�ѭ����Ƶ
	m_PlayingLoopAudio = s;

	//������Ƶ���õ�����
	i->second._c = FSOUND_Stream_Play(FSOUND_FREE, i->second._s);

	//��������
	FSOUND_SetVolume(i->second._c, m_LoopVolume);

	return true;
}

bool CAudioManager::StopLoopAudio(const char* Key)
{
	std::string s = Key;

	//������ǵ�ǰ���ڲ��ŵ���Ƶ����ʧ��
	if (m_PlayingLoopAudio != s)
		return false;

	//�޷��ҵ�Key��ָ������Ƶ�򷵻�ʧ��
	std::map<std::string, _LOOPAUDIO>::iterator i = m_LoopAudio.find(s);
	if (i == m_LoopAudio.end())
		return false;

	//���õ�ǰ�������κ���Ƶ
	m_PlayingLoopAudio = "";

	//ֹͣ��ʽ��Ƶ�Ĳ���
	FSOUND_Stream_Stop(i->second._s);

	//��������
	i->second._c = -1;

	return true;
}

bool CAudioManager::PlayOnceAudio(const char* Key)
{
	std::string s = Key;
	std::map<std::string, FSOUND_SAMPLE*>::iterator i = m_OnceAudio.find(s);
	if (i == m_OnceAudio.end())
		return false;

	//������Ƶ����������
	FSOUND_SetVolume(FSOUND_PlaySound(FSOUND_FREE, i->second), m_OnceVolume);
	return true;
}

int CAudioManager::GetLoopVolume()
{
	//����ѭ����Ƶ����
	return m_LoopVolume;
}

bool CAudioManager::SetLoopVolume(int Volume)
{
	//������ںϷ���Χ�ڷ���ʧ��
	if (Volume < 0 || Volume > 255)
		return false;

	//�����ǰ��ѭ����Ƶ�ڲ���
	if (m_PlayingLoopAudio != std::string(""))
	{
		//���ø���Ƶ������
		FSOUND_SetVolume(m_LoopAudio.find(m_PlayingLoopAudio)->second._c, m_LoopVolume);
	}
	
	//�õ�����
	m_LoopVolume = Volume;

	return true;
}

int CAudioManager::GetOnceVolume()
{
	//���ط�ѭ����Ƶ����
	return m_OnceVolume;
}

bool CAudioManager::SetOnceVolume(int Volume)
{
	//������ںϷ���Χ�ڷ���ʧ��
	if (Volume < 0 || Volume > 255)
		return false;
	
	//�õ�����
	m_OnceVolume = Volume;
	return true;
}

