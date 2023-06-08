#pragma once
#include "ActionBase.h"
class WaitAction :
    public ActionBase
{
public:
	static WaitAction* GetInstance()
	{
		static WaitAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

