///////////////////////////////////////////////
///      ダウン時、怯み時に動く
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

	// 判定
	virtual bool Judgment(GameObject* enemy);
};

