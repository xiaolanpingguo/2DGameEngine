#ifndef _SCENE_CHANGE_H_
#define _SCENE_CHANGE_H_

class CSceneChange
{
	friend class CGameEngine;
	int m_AllFrame; //��֡��
	int m_CurFrame; //��ǰ֡��

public:
	CSceneChange(int AllFrame);
	virtual void Render(int CurFrame);
};

#endif