#include <stdio.h>
#include "CloseRangeAT.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE CloseRangeAT::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->CloseRangeAT();
}
