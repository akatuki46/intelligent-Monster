#include "MediumRangeJM.h"
#include "Enemy.h"
#include "GameObject.h"

bool MediumRangeJM::Judgment(GameObject* enemy)
{
	//プレイヤーとの距離が5以下なら
	if (enemy->GetComponent<Enemy>()->GetLength() <= 8.0f && enemy->GetComponent<Enemy>()->GetLength() > 5.0f)
	{
		return true;
	}

    return false;
}
