#include <stdlib.h>
#include "LongRangeJM.h"
#include "Enemy.h"
#include "GameObject.h"

bool LongRangeJM::Judgment(GameObject* enemy)
{
	if (enemy->GetComponent<Enemy>()->GetActionFlag(Enemy::LongRange_Judgment))
	{
		return true;
	}

	//ƒvƒŒƒCƒ„[‚ðŒ©‚Â‚¯‚Ä‚¢‚½‚ç
	if (enemy->GetComponent<Enemy>()->GetLength() > 8.0f)
	{
		return true;
	}


	return false;
}
