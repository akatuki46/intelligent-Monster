#include "ChargeJudgment.h"
#include "manager.h"
#include "Enemy.h"
#include "Scene.h"


bool ChargeJudgment::Judgment(GameObject* enemy)
{
    if (enemy->GetComponent<Enemy>()->GetActionFlag(Enemy::Charge_Judgment))
    {
        return true;
    }


    if (enemy->GetComponent<Enemy>()->GetChargeCnt() < 3 && enemy->GetComponent<Enemy>()->GetLength() > 7.0f)
    {
        return true;
    }
    return false;
}
