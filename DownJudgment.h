///////////////////////////////////////////////
///      ƒ_ƒEƒ“A‹¯‚İ‚É“®‚­
//////////////////////////////////////////////

#pragma once
#include "ExecJudgmentBase.h"
class DownJudgment :
    public ExecJudgmentBase
{
public:
	static DownJudgment* GetInstance()
	{
		static DownJudgment m_Instance;
		return &m_Instance;
	}

	// ”»’è
	virtual bool Judgment(GameObject* enemy);
};

