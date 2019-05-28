#ifndef _SCENE_H_
#define _SCENE_H_

#include <map>
#include <string>

class CUI;

class CScene
{
	friend class CGameEngine;

	//����л�����
	std::string m_EnterChange;
	std::string	m_QuitChange;

	//�ؼ�����
	std::map<std::string, CUI*> m_UI;
	CUI* m_KeyUI; //ӵ�е�ǰ����Ŀؼ�

public:
	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();
	virtual void OutputRun(); //����
	virtual void LogicInputRun(); //�߼�������
	virtual void Quit();
	virtual void End();

	//�л����
	void SetEnterChange(const char* id);
	void SetQuitChange(const char* id);

	//�ؼ����
	bool LoadUI(const char* id, CUI* pUI);
	bool ReleaseUI(const char* id);
	CUI* GetUI(const char* id);
	CUI* GetKeyUI();
	bool SetKeyUI(const char* id); //��idΪ0�����õ�ǰû�н���ؼ�

	//���������еĿؼ��������鱾�����ͻᱻ����
	virtual void OnUIMsg(const char* id, int UIMSG);
};

#endif