#include <stdio.h>
#include "ApproachAction.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE ApproachAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->ApproachAction();
}
