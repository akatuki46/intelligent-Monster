#include "ChargeAction.h"
#include "Enemy.h"
#include "GameObject.h"

//�`���[�W�s�����s
ActionBase::STATE ChargeAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->Charge();
}
