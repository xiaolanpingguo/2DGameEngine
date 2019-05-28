#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <windows.h>
#include <string>
#include <map>
#include "GameInput.h"
#include "GameOutput.h"
#include "AudioManager.h"
#include "ReadFile.h"
#include "WriteFile.h"

class CScene;
class CSceneChange;

class CGameEngine
{
	//�������
	WNDCLASSA m_WndClass;
	char m_WndClassName[32];
	HWND m_hWnd;
	int m_ClientW, m_ClientH;
	BOOL m_Act;
	int m_SleepTime;
	POINT m_PrePos; //�ղŵĹ��λ��
	bool m_DoubleByte; //˫�ֽ����ֱ�ʶ
	char m_FirstByte; //˫�ֽ��������ֽ�

	//�������
	CGameInput* m_GI;
	CGameOutput* m_GO;
	CReadFile m_RF;
	CWriteFile m_WF;
	CAudioManager m_AM;

	//�������
	std::map<std::string, CScene*> m_Scene; //����
	CScene* m_CurScene; //��ǰ����
	CScene* m_NextScene; //��һ������
	int m_RunState; //����״̬

	//�����л����
	CSceneChange* m_EnterChange;
	CSceneChange* m_QuitChange;
	std::map<std::string, CSceneChange*> m_SceneChange; //�����л�

	//��Ϣ������
	static LRESULT CALLBACK _WindowProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	//�л�����
	void _SceneChange();
	void _Change();

	//���졢������ָ��
	CGameEngine();
	~CGameEngine();
	static CGameEngine* m_pGameEngine;


	void _SendMouseMove();

public:

	//�õ���Ϸ����
	static CGameEngine* GetGE();

	//��ʼ��
	bool Init(
		int ClientW, //�ͻ�����
		int ClientH); //�ͻ�����

	//����
	void Run();

	//������غ���
	bool LoadScene(const char* id, CScene* pScene);
	bool ReleaseScene(const char* id);
	bool SetInitScene(const char* id);
	bool SetCurScene(const char* id);
	CScene* GetScene(const char* id);

	//���س����л�
	bool LoadSceneChange(const char* id, CSceneChange* pSceneChange);

	//���ߺ���
	CGameInput* GetGI();
	CGameOutput* GetGO();
	void SetTitle(const char* Title);
	bool SetSleepTime(int SleepTime);
	void ExitGame();
	int GetW();
	int GetH();
	static int GetRandomNum(int Min, int Max);

	CReadFile* GetRF();
	CWriteFile* GetWF();
	CAudioManager* GetAM();
};

#endif