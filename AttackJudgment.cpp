#include <stdlib.h>
#include "AttackJudgment.h"
#include "Enemy.h"
#include "GameObject.h"

bool AttackJudgment::Judgment(GameObject *enemy)
{
	//プレイヤーを見つけていたら
	if (enemy->GetComponent<Enemy>()->FindPlayer())
	{
		return true;
	}

	return false;
}