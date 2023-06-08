#pragma once
#include "ActionBase.h"
class GameObject;

class ChargeAction :
    public ActionBase
{
public:
	static ChargeAction* GetInstance()
	{
		static ChargeAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

