#pragma once
#include "ExecJudgmentBase.h"

class GameObject;

//待機判定用クラス
class WaitJudgment :
    public ExecJudgmentBase
{
public:
	static WaitJudgment* GetInstance()
	{
		static WaitJudgment m_Instance;
		return &m_Instance;
	}

	// 判定
	virtual bool Judgment(GameObject* enemy);

};

