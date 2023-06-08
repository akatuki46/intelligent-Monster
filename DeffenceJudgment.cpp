#include "DeffenceJudgment.h"
#include "Enemy.h"
#include "GameObject.h"

//�h��s������֐�
bool DeffenceJudgment::Judgment(GameObject *enemy)
{
	if (enemy->GetComponent<Enemy>()->GetActionFlag(Enemy::Deffence_Judgment))
	{
		enemy->GetComponent<Enemy>()->LostPlayer();
		return true;
	}

	if (!enemy->GetComponent<Enemy>()->FindPlayer())
	{
		return true;
	}

	return false;
}
