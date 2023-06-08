///////////////////////////////////////////////
///      ���S���ɓ���
//////////////////////////////////////////////

#pragma once
#include "ExecJudgmentBase.h"

class GameObject;

class DieJudgment :
	public ExecJudgmentBase
{
public:
	static DieJudgment* GetInstance()
	{
		static DieJudgment m_Instance;
		return &m_Instance;
	}

	// ����
	virtual bool Judgment(GameObject* enemy);

};

