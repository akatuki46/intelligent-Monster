#include "TackleAction.h"
#include <stdio.h>
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE TackleAction::Run(GameObject* enemy)
{
	return enemy->GetComponent<Enemy>()->Tackle();
}
