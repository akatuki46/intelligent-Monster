///////////////////////////////////////////////
///      �_�E�����A���ݎ��ɓ���
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

	// ����
	virtual bool Judgment(GameObject* enemy);
};

