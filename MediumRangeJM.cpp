#include "MediumRangeJM.h"
#include "Enemy.h"
#include "GameObject.h"

bool MediumRangeJM::Judgment(GameObject* enemy)
{
	//�v���C���[�Ƃ̋�����5�ȉ��Ȃ�
	if (enemy->GetComponent<Enemy>()->GetLength() <= 8.0f && enemy->GetComponent<Enemy>()->GetLength() > 5.0f)
	{
		return true;
	}

    return false;
}
