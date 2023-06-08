#include "CloseDis.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE CloseDis::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->CloseDis();
}
