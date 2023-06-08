#pragma once
#include "ActionBase.h"
class GameObject;

class DieAction :
    public ActionBase
{
public:
	static DieAction* GetInstance()
	{
		static DieAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

