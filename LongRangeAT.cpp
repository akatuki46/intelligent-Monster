#include <stdio.h>
#include "LongRangeAT.h"
#include "Enemy.h"
#include "GameObject.h"

ActionBase::STATE LongRangeAT::Run(GameObject* enemy)
{
    //�������U�������s
    return enemy->GetComponent<Enemy>()->LongRangeAT();
}
