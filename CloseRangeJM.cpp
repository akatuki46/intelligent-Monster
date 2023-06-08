#include "CloseRangeJM.h"
#include "Enemy.h"
#include "GameObject.h"

bool CloseRangeJM::Judgment(GameObject* enemy)
{
	if (enemy->GetComponent<Enemy>()->GetActionFlag(Enemy::CloseRange_Judgment))
	{
		return true;
	}

	//�v���C���[�Ƃ̋�����5�ȉ��Ȃ�
	if (enemy->GetComponent<Enemy>()->GetLength() <= 5.0f)
	{
		return true;
	}
	return false;
}