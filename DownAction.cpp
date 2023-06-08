#include "DownAction.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE DownAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->Down();
}