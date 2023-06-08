#pragma once
#include "ActionBase.h"
class GameObject;

class ApproachAction :
    public ActionBase
{
public:
	static ApproachAction* GetInstance()
	{
		static ApproachAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

