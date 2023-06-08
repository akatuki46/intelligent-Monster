#include "WaitAction.h"
#include <stdio.h>
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE WaitAction::Run(GameObject* enemy)
{
	return enemy->GetComponent<Enemy>()->Wait();
}
