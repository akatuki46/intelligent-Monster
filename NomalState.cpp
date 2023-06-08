#include "NomalState.h"
#include "manager.h"
#include "Scene.h"
#include "Enemy.h"
#include "ChargeState.h"
#include "Motion.h"
#include "Particle.h"

void NomalState::Action()
{
	pEnemy->GetComponent<Motion>()->SetShaderCnt(0);
	//pEnemy->GetComponent<Particle>()->SetUse(false);

	//�`���[�W�񐔂�3��ɂȂ�����ѓd��Ԃֈڍs
	if (pEnemy->GetComponent<Enemy>()->GetChargeCnt() == 3)
	{
		pEnemy->GetComponent<Enemy>()->NextSituation(new ChargeState(pEnemy));
	}
}

int NomalState::GetStatus()
{
	return 1;
}
