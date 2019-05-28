#include "1.h"
#include "GameEngine.h"
#include "ButtonUI.h"
#include "EditUI.h"
#include "SelectUI.h"
void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	CGameEngine::GetGE()->GetGO()->LoadFont(
		"��ʼ��������",
		30, 20, 400, false, false, false, "����");

	SetEnterChange("��4");
	SetQuitChange("��4");

	LoadUI("��ʼ��ť", new CButtonUI("Start", 0, 0, 100, 30));
	LoadUI("������ť", new CButtonUI("Exit", 0, 200, 100, 30));

	GetUI("������ť")->SetAct(false);

	LoadUI("�༭��1",new CEditUI(0,"123abc",150,200,200,80));
	LoadUI("�༭��2",new CEditUI(16,0,150,300,200,60));

	LoadUI("ѡ��1",new CSelectUI("����",0,255,CGameEngine::GetGE()->GetAM()->GetLoopVolume(),150,100,200,60));
	LoadUI("ѡ��2",new CSelectUI("��Ч",0,255,CGameEngine::GetGE()->GetAM()->GetOnceVolume(),400,100,160,40));

	CGameEngine::GetGE()->GetAM()->PushLoopAudio("m1","sound\\m1.mp3");
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("m2","sound\\m2.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("e1","sound\\e1.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("e2","sound\\e2.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("e3","sound\\e3.mp3");
}

void C1::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp2(
		"pic\\Bliss.bmp",
		0, 0, 640, 480,
		0, 0);

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"��ʼ��������", 0, 0, "���س�������Ϸ", RGB(255, 0, 0));

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"��ʼ��������", 0, 50, "��ESC�˳���Ϸ", RGB(255, 0, 255));
}

void C1::LogicInputRun()
{
}

void C1::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "��ʼ��ť") == 0)
		{
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("e1");
			CGameEngine::GetGE()->SetCurScene("��Ϸ����");
		}
		else if (strcmp(id, "������ť") == 0)
			CGameEngine::GetGE()->ExitGame();
	}
	else if(UIMSG == _SELECT_NUM_CHANGE)
	{
		if(strcmp(id,"ѡ��1") == 0)
		{
			int cur = ((CSelectUI*)GetUI("ѡ��1"))->GetCur();
			CGameEngine::GetGE()->GetAM()->SetLoopVolume(cur);
		}
		else if(strcmp(id,"ѡ��2") == 0)
		{
			int cur = ((CSelectUI*)GetUI("ѡ��2"))->GetCur();
			CGameEngine::GetGE()->GetAM()->SetLoopVolume(cur);
		}
	}
}

void C1::Enter()
{
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("m1");
}
void C1::Quit()
{
	CGameEngine::GetGE()->GetAM()->StopLoopAudio("m1");
}
