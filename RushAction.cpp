#include "RushAction.h"
#include "Enemy.h"
#include "GameObject.h"

//�`���[�W�s�����s
ActionBase::STATE RushAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->Rush();
}
