#ifndef ATTACK_ACTION_H_
#define ATTACK_ACTION_H_

#include "ActionBase.h"

class GameObject;

// éÁîıçsìÆ
class AttackAction : public ActionBase
{
public:
	static AttackAction* GetInstance()
	{
		static AttackAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject* enemy);
};

#endif