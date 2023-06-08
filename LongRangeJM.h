#pragma once
#include "ExecJudgmentBase.h"
class GameObject;

class LongRangeJM :
    public ExecJudgmentBase
{
public:
	static LongRangeJM* GetInstance()
	{
		static LongRangeJM m_Instance;
		return &m_Instance;
	}

	// ”»’è
	virtual bool Judgment(GameObject* enemy);

};

