#include "WaitJudgment.h"
#include <stdlib.h>
#include "Enemy.h"
#include "GameObject.h"

bool WaitJudgment::Judgment(GameObject* enemy)
{
	//ƒvƒŒƒCƒ„[‚ðŒ©‚Â‚¯‚Ä‚¢‚½‚ç
	if (enemy->GetComponent<Enemy>()->GetRayCollision())
	{
		return true;
	}
	return false;

}
