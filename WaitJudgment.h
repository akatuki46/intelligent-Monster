#pragma once
#include "ExecJudgmentBase.h"

class GameObject;

//�ҋ@����p�N���X
class WaitJudgment :
    public ExecJudgmentBase
{
public:
	static WaitJudgment* GetInstance()
	{
		static WaitJudgment m_Instance;
		return &m_Instance;
	}

	// ����
	virtual bool Judgment(GameObject* enemy);

};

