#include <stdlib.h>
#include "AttackJudgment.h"
#include "Enemy.h"
#include "GameObject.h"

bool AttackJudgment::Judgment(GameObject *enemy)
{
	//�v���C���[�������Ă�����
	if (enemy->GetComponent<Enemy>()->FindPlayer())
	{
		return true;
	}

	return false;
}