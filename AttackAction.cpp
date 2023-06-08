#include <stdio.h>
#include "AttackAction.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE AttackAction::Run(GameObject* enemy)
{
	return enemy->GetComponent<Enemy>()->Attack();
}