#pragma once
#include "ActionBase.h"
class CloseDis :
    public ActionBase
{

public:
	static CloseDis* GetInstance()
	{
		static CloseDis instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

