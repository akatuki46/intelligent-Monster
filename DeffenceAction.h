#ifndef DEFFENCE_ACTION_H_
#define DEFFENCE_ACTION_H_

#include "ActionBase.h"

class GameObject;

// éÁîıçsìÆ
class DeffenceAction : public ActionBase
{
public:
	static DeffenceAction *GetInstance()
	{
		static DeffenceAction instance;
		return &instance;
	}

	virtual STATE Run(GameObject *enemy);
};

#endif
