#pragma once
#include "ActionBase.h"
class GameObject;

class DownAction :
    public ActionBase
{
public:
	static DownAction* GetInstance()
	{
		static DownAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

