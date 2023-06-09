///////////////////////////////////////////////
///      死亡時に動く
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

	// 判定
	virtual bool Judgment(GameObject* enemy);

};

