#include "DownJudgment.h"
#include "Enemy.h"
#include "GameObject.h"
bool DownJudgment::Judgment(GameObject* enemy)
{

	if (enemy->GetComponent<Enemy>()->GetFearFlag())
	{
		return true;
	}

    return false;
}
