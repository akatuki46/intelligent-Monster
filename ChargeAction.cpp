#include "ChargeAction.h"
#include "Enemy.h"
#include "GameObject.h"

//チャージ行動実行
ActionBase::STATE ChargeAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->Charge();
}
