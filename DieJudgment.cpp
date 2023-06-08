#include "Diejudgment.h"
#include "Enemy.h"
#include "GameObject.h"

bool DieJudgment::Judgment(GameObject* enemy)
{
	if (enemy->GetComponent<Enemy>()->GetEnemyHp() <= 0)
	{
		return true;
	}

	return false;
}
