#include "MediumRangeJM.h"
#include "Enemy.h"
#include "GameObject.h"

bool MediumRangeJM::Judgment(GameObject* enemy)
{
	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ª5ˆÈ‰º‚È‚ç
	if (enemy->GetComponent<Enemy>()->GetLength() <= 8.0f && enemy->GetComponent<Enemy>()->GetLength() > 5.0f)
	{
		return true;
	}

    return false;
}
