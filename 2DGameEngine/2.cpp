#include "2.h"
#include "GameEngine.h"
#include "BmpButtonUI.h"
#include "ButtonUI.h"

void C2::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadFont(
		"��Ϸ��������",
		40, 40, 400, false, false, false, "����");

	x = y = 0;

	SetEnterChange("��4");
	SetQuitChange("��4");

	LoadUI("���ذ�ť1",new CButtonUI("Return",0,0,100,30));

	LoadUI("���ذ�ť2",new CBmpButtonUI(
		"pic\\b1_0.bmp",
		"pic\\b1_1.bmp",
		"pic\\b1_2.bmp",
		"pic\\b1_3.bmp",
		200,200,75,40,true,RGB(0,255,0)));

	LoadUI("123",new CBmpButtonUI(
		"pic\\b1_0.bmp",
		"pic\\b1_1.bmp",
		"pic\\b1_2.bmp",
		"pic\\b1_3.bmp",
		300,200,75,40,true,RGB(0,255,0)));

	GetUI("123")->SetAct(false);
}

void C2::Enter()
{
	time = 0;
}

void C2::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp2(
		"pic\\δ����.bmp",
		0, 0, 640, 480,
		0, 0);

	CGameEngine::GetGE()->GetGO()->DrawBmp1(
		"pic\\1.bmp",
		x, y, 40, 70,
		0, 0);

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"��Ϸ��������", 0, 0, "��ESC����", RGB(255, 255, 0));
}

void C2::LogicInputRun()
{
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_W) == _KS_DH)
		y -= 5;

	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_S) == _KS_DH)
		y += 5;

	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_A) == _KS_DH)
		x -= 5;

	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_D) == _KS_DH)
		x += 5;

	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_RETURN) == _KS_DH)
		CGameEngine::GetGE()->GetAM()->PlayOnceAudio("e2");

	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_ESC) == _KS_UC)
		CGameEngine::GetGE()->SetCurScene("��ʼ����");
}

void C2::OnUIMsg(const char* id, int UIMSG)
{
	if(UIMSG == _BUTTON_CLICK)
	{
		if(strcmp(id,"���ذ�ť1") == 0)
		{
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("e3");
			CGameEngine::GetGE()->SetCurScene("��ʼ����");
		}
		if(strcmp(id,"���ذ�ť2") == 0)
		{
			Beep(500,1000);
			CGameEngine::GetGE()->SetCurScene("��ʼ����");
		}
	}
}

void C2::Quit()
{
	CGameEngine::GetGE()->GetAM()->StopLoopAudio("m2");
}