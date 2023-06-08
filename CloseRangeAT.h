#pragma once
#include "ActionBase.h"
class GameObject;

class CloseRangeAT :
	public ActionBase
{
public:
	static CloseRangeAT* GetInstance()
	{
		static CloseRangeAT instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

