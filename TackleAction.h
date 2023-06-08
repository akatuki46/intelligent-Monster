#pragma once
#include "ActionBase.h"
class TackleAction :
	public ActionBase
{
public:
	static TackleAction* GetInstance()
	{
		static TackleAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

