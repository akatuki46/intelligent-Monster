#pragma once
#include "ActionBase.h"
class GameObject;

class LongRangeAT :
    public ActionBase
{

public:
	static LongRangeAT* GetInstance()
	{
		static LongRangeAT instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);

};

