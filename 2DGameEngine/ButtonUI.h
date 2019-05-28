#ifndef _BUTTON_UI_H_
#define _BUTTON_UI_H_

#include "UI.h"
#include <string>

#define _BUTTON_CLICK 0 //��ť��������Ϣ

#define _BUTTON_STATE_CURSOR_OUT		0  //���������
#define _BUTTON_STATE_CURSOR_IN_UP		1  //�������̧��
#define _BUTTON_STATE_CURSOR_IN_DOWN	2  //������ڰ���

class CButtonUI : public CUI
{
	//bool m_In; //����ڰ�ť��
	//std::string m_Text; //��ť������
protected:
	int m_ButtonState;//��ť״̬
	bool m_DownIn;//�Ƿ��ڰ�ť�ϰ���
	std::string m_Text; //��ť������

public:
	CButtonUI(const char* t, int x, int y, int w, int h, bool v = true, bool a = true);

	//virtual void Init();
	virtual void ActRender();
	virtual void UnactRender();
	virtual void OnMsg(int Msg, int p1, int p2);
	//virtual void End();

	void SetText(const char* t);
	const char* GetText();
};

#endif