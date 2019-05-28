#ifndef _SELECT_UI_H_
#define _SELECT_UI_H_

#include "UI.h"
#include <string>

#define _SELECT_NUM_CHANGE 2 //���ֱ��ı���Ϣ

class CSelectUI : public CUI
{
protected:
	int m_Min, m_Max, m_Cur; //��Сֵ�����ֵ����ǰֵ
	std::string m_Text; //��ť������
	bool m_In; //������ڲ�
	bool m_Down; //���±�־
	int m_Pos; //�����ұ�־-1��0��1��ʾ������

public:
	CSelectUI(const char* t, int min, int max, int cur, int x, int y, int w, int h, bool v = true, bool a = true);

	//virtual void Init();
	virtual void ActRender();
	virtual void UnactRender();
	virtual void OnMsg(int Msg, int p1, int p2);
	//virtual void End();

	void SetText(const char* t);
	const char* GetText();

	bool SetCur(int cur);
	int GetCur();
};

#endif