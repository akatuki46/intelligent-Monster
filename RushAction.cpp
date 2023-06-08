#include "RushAction.h"
#include "Enemy.h"
#include "GameObject.h"

//チャージ行動実行
ActionBase::STATE RushAction::Run(GameObject* enemy)
{
    return enemy->GetComponent<Enemy>()->Rush();
}
