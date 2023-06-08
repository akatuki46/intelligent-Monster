#pragma once
#include "ExecJudgmentBase.h"
class GameObject;

class CloseRangeJM :
    public ExecJudgmentBase
{
public:
	static CloseRangeJM* GetInstance()
	{
		static CloseRangeJM m_Instance;
		return &m_Instance;
	}

	// ”»’è
	virtual bool Judgment(GameObject* enemy);

};

