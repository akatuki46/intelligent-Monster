#include "WaitJudgment.h"
#include <stdlib.h>
#include "Enemy.h"
#include "GameObject.h"

bool WaitJudgment::Judgment(GameObject* enemy)
{
	//プレイヤーを見つけていたら
	if (enemy->GetComponent<Enemy>()->GetRayCollision())
	{
		return true;
	}
	return false;

}
