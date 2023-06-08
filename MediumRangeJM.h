#pragma once
#include "ExecJudgmentBase.h"

class MediumRangeJM :
    public ExecJudgmentBase
{
public:
	static MediumRangeJM* GetInstance()
	{
		static MediumRangeJM m_Instance;
		return &m_Instance;
	}

	// ”»’è
	virtual bool Judgment(GameObject* enemy);

};

