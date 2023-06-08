///////////////////////////////////////////////
///      Ž€–SŽž‚É“®‚­
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

	// ”»’è
	virtual bool Judgment(GameObject* enemy);

};

