#ifndef _BMP_BUTTON_UI_H_
#define _BMP_BUTTON_UI_H_

#include "ButtonUI.h"
#include <string>
#include <windows.h>


class CBmpButtonUI : public CButtonUI
{
	std::string s[4];
	bool m_Transparent;//�Ƿ�Ҫ͸��
	unsigned int m_TC;//͸����ɫ
public:
	CBmpButtonUI(const char* bmp_act_cursor_out,
		const char* bmp_act_cursor_in_up,
		const char* bmp_act_cursor_in_down,
		const char* bmp_unact,
		int x,
		int y,
		int w,
		int h,
		bool t = true,//͸�����
		unsigned int tc = RGB(0,255,0),//͸����ɫ
		bool v = true,
		bool a = true);

	//virtual void Init();
	virtual void ActRender();
	virtual void UnactRender();
	//virtual void OnMsg(int Msg, int p1, int p2);
	//virtual void End();

	//void SetText(const char* t);
	//const char* GetText();
};

#endif