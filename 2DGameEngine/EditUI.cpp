#include "EditUI.h"
#include "Scene.h"
#include "GameEngine.h"
#include <windows.h>
#include <ctype.h>

void CEditUI::_Add(int size)
{
	if (m_TextSize - m_TextLength - 1 < size)
	{
		m_TextSize += size;
		m_TextSize *= 2;
		char* p = new char[m_TextSize];
		strcpy_s(p, m_TextSize, m_Text);
		delete [] m_Text;
		m_Text = p;
	}
}

CEditUI::CEditUI(int max, const char* t, int x, int y, int w, int h, bool v, bool a)
:
CUI(x, y, w, h, v, a),
m_Max(max),
m_Edit(false),
m_TextSize(t ? (int)strlen(t) + 1 : 32),
m_TextLength(t ? (int)strlen(t) : 0),
m_Text(new char[m_TextSize])
{
	if (t)
		strcpy_s(m_Text, m_TextSize, t);
	else
		m_Text[m_TextLength] = 0;
}

CEditUI::~CEditUI()
{
	delete [] m_Text;
}

void CEditUI::ActRender()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();

	pGO->DrawRectangle2(
		m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0, 0, 0),
		m_Edit ? RGB(255, 255, 255) : RGB(175, 175, 175));

	pGO->DrawString2(
		0,
		m_X, m_Y, m_W, m_H,
		m_Text,
		RGB(0, 0, 0));
}

void CEditUI::UnactRender()
{
	CGameOutput* pGO = CGameEngine::GetGE()->GetGO();

	pGO->DrawRectangle2(
		m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0, 0, 0),
		RGB(175, 175, 175));

	pGO->DrawString2(
		0,
		m_X, m_Y, m_W, m_H,
		m_Text,
		RGB(100, 100, 100));
}

void CEditUI::OnMsg(int Msg, int p1, int p2)
{
	switch (Msg)
	{
	case _UIM_C_LBD_IN:
		{
			m_Edit = true;
			m_Scene->SetKeyUI(m_Name.c_str());
			break;
		}
	case _UIM_C_LBD_OUT:
		{
			m_Edit = false;
			if (m_Scene->GetKeyUI() == this)
				m_Scene->SetKeyUI(0);
			break;
		}
	case _UIM_K_CHAR:
		{
			if (p2) //˫�ֽ�(һ�����Դ�ӡ)
			{
				if (m_Max == 0 || (m_Max > 0 && m_TextLength + 2 <= m_Max))
				{
					_Add(2);
					char* q = (char*)&p1;
					m_Text[m_TextLength] = q[0];
					m_Text[m_TextLength + 1] = q[1];
					m_TextLength += 2;
					m_Text[m_TextLength] = 0;
					m_Scene->OnUIMsg(m_Name.c_str(), _EDIT_TEXT_CHANGE);
				}
			}
			else //���ֽ�(��Ϊ��ӡ������)
			{
				//�˸�
				if (p1 == 8)
				{
					//����������
					if (m_TextLength > 0)
					{
						bool db;
						for (int i = 0; i < m_TextLength; ++i)
						{
							if (IsDBCSLeadByte(m_Text[i]))
							{
								db = true;
								i += 1;
							}
							else
								db = false;
						}
						m_Text[m_TextLength -= (db ? 2 : 1)] = 0;
					}
				}
				//���˸�
				else
				{
					//���Դ�ӡ���������ַ���
					if (isprint(p1))
					{
						if (m_Max == 0 || (m_Max > 0 && m_TextLength + 1 <= m_Max))
						{
							_Add(1);
							m_Text[m_TextLength] = (char)p1;
							m_TextLength += 1;
							m_Text[m_TextLength] = 0;
							m_Scene->OnUIMsg(m_Name.c_str(), _EDIT_TEXT_CHANGE);
						}
					}
				}
			}

			break;
		}
	}
}

void CEditUI::SetText(const char* t)
{
	int len = (int)strlen(t);

	if (m_TextSize - 1 >= len)
		strcpy_s(m_Text, m_TextSize, t);
	else
	{
		delete [] m_Text;
		m_Text = new char[m_TextSize = len + 1];
		strcpy_s(m_Text, m_TextSize, t);
	}

	m_TextLength = len;
}

const char* CEditUI::GetText()
{
	return m_Text;
}