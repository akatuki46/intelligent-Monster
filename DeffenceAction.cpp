#include <stdio.h>
#include "DeffenceAction.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE DeffenceAction::Run(GameObject *enemy)
{
	return enemy->GetComponent<Enemy>()->Deffence();
}