#ifndef _2_H_
#define _2_H_

#include "Scene.h"

class C2 : public CScene
{
	int x, y;
	int time;

public:
	//virtual ~CScene();

	virtual void Init();
	virtual void Enter();
	virtual void OutputRun(); //����
	virtual void LogicInputRun(); //�߼�������
	virtual void Quit();
	//virtual void End();

	void OnUIMsg(const char* id, int UIMSG);
};

#endif