#pragma once
#include "ActionBase.h"
class RushAction :
    public ActionBase
{
public:
	static RushAction* GetInstance()
	{
		static RushAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

