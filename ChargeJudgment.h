#pragma once
#include "ExecJudgmentBase.h"
class GameObject;

class ChargeJudgment :
    public ExecJudgmentBase
{
public:
	static ChargeJudgment* GetInstance()
	{
		static ChargeJudgment m_Instance;
		return &m_Instance;
	}

	// ����
	virtual bool Judgment(GameObject* enemy);

};

