#include "CloseRangeJM.h"
#include "Enemy.h"
#include "GameObject.h"

bool CloseRangeJM::Judgment(GameObject* enemy)
{
	if (enemy->GetComponent<Enemy>()->GetActionFlag(Enemy::CloseRange_Judgment))
	{
		return true;
	}

	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ª5ˆÈ‰º‚È‚ç
	if (enemy->GetComponent<Enemy>()->GetLength() <= 5.0f)
	{
		return true;
	}
	return false;
}