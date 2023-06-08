#include <stdio.h>
#include "LongRangeAT.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE LongRangeAT::Run(GameObject* enemy)
{
    //‰“‹——£UŒ‚‚ðŽÀs
    return enemy->GetComponent<Enemy>()->LongRangeAT();
}
