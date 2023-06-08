#include "DieAction.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE DieAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->Die();
}