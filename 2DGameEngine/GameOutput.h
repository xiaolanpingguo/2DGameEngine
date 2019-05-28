#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <string>
#include <map>

#define _MIRROR_NONE 0 //������
#define _MIRROR_LR 1 //���Ҿ���
#define _MIRROR_TB 2 //���¾���
#define _MIRROR_LRTB 3 //�������¾���

class CGameOutput
{
	HWND m_hWnd; //����
	int m_ClientW, m_ClientH; //���ڿͻ������
	HDC m_MainDC; //���豸
	HDC m_BackDC; //���豸
	HDC m_MirrorDC; //�����豸
	HDC m_DarkDC; //�����豸
	unsigned char m_Dark; //����
	std::map<std::string, HDC> m_Bmp; //λͼӳ��
	std::map<std::string, HFONT> m_Font; //����ӳ��

public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	//��ʼ����������
	void Begin();
	void End();

	//��ȡ����������
	unsigned char GetDark();
	void SetDark(unsigned char d);

	//ͼԪ���
	void DrawLine( //����
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0, 0, 0),
		int w = 1);
	void DrawRectangle1( //�����ľ���
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0, 0, 0));
	void DrawRectangle2( //��ʵ�ľ���
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int pc = RGB(0, 0, 0),
		unsigned int bc = RGB(255, 255, 255));
	void DrawEllipse1( //��������Բ
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0, 0, 0));
	void DrawEllipse2( //��ʵ����Բ
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int pc = RGB(0, 0, 0),
		unsigned int bc = RGB(255, 255, 255));

	//λͼ���
	bool LoadBmp(const char* fn);
	bool ReleaseBmp(const char* fn);
	int LoadDirectory(const char* dn);
	bool DrawBmp1( //����͸��ɫλͼ
		const char* fn,
		int dx,
		int dy,
		int dw,
		int dh,
		int sx,
		int sy,
		char m = _MIRROR_NONE,
		unsigned int tc = RGB(0, 255, 0));
	bool DrawBmp2( //����λͼ
		const char* fn,
		int dx,
		int dy,
		int dw,
		int dh,
		int sx,
		int sy,
		char m = _MIRROR_NONE);

	//�������
	bool LoadFont(
		const char* id, //����id
		int w = 0, //�����
		int h = 0, //�����
		int we = 400, //�����ϸ
		bool i = false, //�Ƿ�Ϊб��
		bool u = false, //�Ƿ����»���
		bool s = false, //�Ƿ��д�Խ��
		const char* fn = "����"); //�����������
	bool ReleaseFont(const char* id);
	bool DrawString1( //���Ƶ�������
		const char* id, //����id(����Ϊ0)
		int x, //�����������Ͻ�x
		int y, //�����������Ͻ�y
		const char* t, //����
		unsigned int c); //��ɫ
	bool DrawString2( //���ƶ�������
		const char* id, //����id(����Ϊ0)
		int x, //���־������Ͻ�x
		int y, //���־������Ͻ�y
		int w, //���־��ο�
		int h, //���־��θ�
		const char* t, //����
		unsigned int c); //��ɫ
	bool DrawString3( //���ƾ��ж����������
		const char* id, //����id(����Ϊ0)
		int x, //���־������Ͻ�x
		int y, //���־������Ͻ�y
		int w, //���־��ο�
		int h, //���־��θ�
		const char* t, //����
		unsigned int c); //��ɫ
};

#endif